#include "stlv.h"
#include "minunit.h"

#define stlv_assert(cond, str) mu_assert("stlv error: " str, cond) 

#define	TAG_ONE	0xDEAD
#define	TAG_TWO	0xBEEF

char *stlv_test_known_data(void)
{
	
}

char *stlv_test_flexible_size(void)
{

}

char *stlv_test_bootstrap(void)
{
	char buffer[100];
	void *tlv_head = (void *)buffer;
	void *tlv_second_entry = 0;

	// Initialize some test values
	uint32_t x = 0x12345678;
	uint16_t y = 0xABCD;
	uint32_t x_copy = 0;
	uint16_t y_copy = 0;

	// Write two entries, saving the position of the second one
	stlv_compose(&tlv_head, TAG_ONE, sizeof(x), &x);
	tlv_second_entry = tlv_head;
	stlv_compose(&tlv_head, TAG_TWO, sizeof(y), &y);
	
	// Read out the first one
	tlv_head = buffer;
	stlv_copy_value(tlv_head, &x_copy);
	stlv_assert((stlv_get_tag(tlv_head) == TAG_ONE), "tlv tag error");
	stlv_assert((stlv_get_length(tlv_head) == sizeof(x)), "tlv length error");
	stlv_assert((x_copy == x), "tlv tag error");

	// Read the second one out
	stlv_next(&tlv_head);
	stlv_assert((tlv_head == tlv_second_entry), "tlv next error");
	stlv_copy_value(tlv_head, &y_copy);
	stlv_assert((stlv_get_tag(tlv_head) == TAG_TWO), "tlv tag error");
	stlv_assert((stlv_get_length(tlv_head) == sizeof(y)), "tlv length error");
	stlv_assert((y_copy == y), "tlv tag error");

	// All set
	return 0;
}

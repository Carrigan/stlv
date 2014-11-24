## Simple TLV Parser/Composer Project
The purpose of this project is to provide a general purpose tag-length-value or type-length-value parser. It defaults to 16 bit tags and an 8 bit length field, meaning the value payload can be up to 256 bytes.

#### Requirements
This library has no requirements outside of the C standard library. In order to build the test suite for PC, minunit, gcc, and make are required.
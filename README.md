# serialization
 compare different approach on serialization

 the definition of serialization from wiki:
 
 [Serialization](https://en.wikipedia.org/wiki/Serialization) is the process of translating a data structure or object state into a format that can be stored (for example, in a file or memory data buffer) or transmitted (for example, across a computer network) and reconstructed later (possibly in a different computer environment).

 to do it, two different approach are proposed.
 
 (1) Boost Serialization:
 - define the serialize function on the target data
 1. ✅ pointer referencing: object tracking on the pointer address
 2. ❌ cross version: user need to handle the version migration on serialize function
 
 (2) Google Protocol Buffer
 - define the IDL and construct the IDL model
 1. ❌ pointer referencing: user need to record the relationship on IDL model
 2. ✅ cross version: protocl buffer support the cross version natively


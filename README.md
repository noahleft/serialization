# serialization
 compare different approach on serialization
 
 Firstly, what is serailization?

 the definition of serialization from wiki:
 
 [Serialization](https://en.wikipedia.org/wiki/Serialization) is the process of translating a data structure or object state into a format that can be stored (for example, in a file or memory data buffer) or transmitted (for example, across a computer network) and reconstructed later (possibly in a different computer environment).

 To do so, two different approaches are proposed.

 symbol meanings:
 - ✅ Pros:    this approach can natively support it.
 - ❌ Cons:    this approach needs extra handling.
 - ⚠️ Neutral: *both* approach needs extra handling.
 
 1. Boost Serialization: (serialize directly)
 > - Define the serialize function on the target data.
 > 1. ✅ pointer referencing: object tracking on the pointer address
 > 2. ❌ cross version: user need to handle the version migration on serialize function
 > 3. ⚠️ inheritance: user need to export the base-derived relationship
 
 2. Google Protocol Buffer: (IDL based)
 > - Define the IDL model. Then, translate the target data to the IDL model.
 > 1. ❌ pointer referencing: user need to record the relationship on IDL model
 > 2. ✅ cross version: protocl buffer support the cross version natively
 > 3. ⚠️ inheritance: user need to record the base-derived relationship on IDL model

# related approach
 1. [application checkpointing](https://en.wikipedia.org/wiki/Application_checkpointing)
 > - Check point the process to disk and restart later. 
 > - Process snapshot.
 > - Ex: Distributed MultiThreaded CheckPointing (DMTCP), Checkpoint/Restore In Userspace (CRIU), Berkeley Lab Checkpoint/Restart (BCLR)
 2. [relational database](https://en.wikipedia.org/wiki/Relational_database)
 > - Use traditional CRUD operations to store the data.
 > - Schema-based
 > - Ex: SQLite
 3. [key-value database](https://en.wikipedia.org/wiki/Key–value_database)
 > - Non-relational database that uses a simple key-value method.
 > - Key-value based (like Hashing)
 > - Ex: Redis


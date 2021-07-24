# serialization
 compare different approach on serialization
 
 Firstly, what is serailization?

 the definition of serialization from wiki:
 
 [Serialization](https://en.wikipedia.org/wiki/Serialization) is the process of translating a data structure or object state into a format that can be stored (for example, in a file or memory data buffer) or transmitted (for example, across a computer network) and reconstructed later (possibly in a different computer environment).

 To do so, two different approaches are proposed.

 symbol meanings:
 - ✅ Pros:    this approach can natively support it.
 - ❌ Cons:    this approach can not handle it well.
 - ⚠️ Neutral: this approach needs some extra handling. But it's do-able in most cases.
 
 1. Boost Serialization: (serialize directly)
 > - Define the serialize function on the target data.
 > 1. ✅ pointer referencing: object tracking on the pointer address
 > 2. ⚠️ cross version: user need to handle the version migration on serialize function
 > 3. ⚠️ inheritance: user need to export the base-derived relationship
 > 4. ❌ development: foreach header change, the developer needs to handle the serialization parts.
 > 5. ✅ memory consumption: serailze *directly*, so no extra memory required.

 2. Boost Serialization + Lex/Yacc code generation: (serialize directly)
 > - Use header file as IDL model to generate the serialize function on the target data.
 > 1. ✅ pointer referencing: object tracking on the pointer address
 > 2. ❌ cross version: user need to handle the version migration on serialize function
 > 3. ⚠️ inheritance: user need to export the base-derived relationship
 > 4. ✅ development: with well-defined code generation, no extra work needed.
 >> In general, code generation would help RD to auto-gen the serialization function. 
 >> But it would cause the side-effect on forward/backward compatible.
 > 5. ✅ memory consumption: serailze *directly*, so no extra memory required.
 
 3. Google Protocol Buffer: (IDL based)
 > - Define the IDL model in ProtoBuf format. Then, translate the target data to the IDL model.
 > 1. ❌ pointer referencing: user need to record the relationship on IDL model. A general solution is indexing.
 > 2. ✅ cross version: protocl buffer support the cross version natively
 > 3. ⚠️ inheritance: user need to record the base-derived relationship on IDL model
 > 4. ✅ development: with well-defined IDL model, no extra work needed.
 > 5. ❌ memory consumption: Extra O(n) space required. ProtoBuf needs to **translate** the target data to required IDL model.
 >> The modification on the generated code is not recommended in ProtoBuf documentation.

# related approach
 1. [application checkpointing](https://en.wikipedia.org/wiki/Application_checkpointing) (Process snapshot)
 > - Check point the process to disk and restart later. 
 > - Ex: Distributed MultiThreaded CheckPointing (DMTCP), Checkpoint/Restore In Userspace (CRIU), Berkeley Lab Checkpoint/Restart (BCLR)
 2. [relational database](https://en.wikipedia.org/wiki/Relational_database) (Schema-based)
 > - Use traditional CRUD operations to store the data.
 > - Ex: SQLite
 3. [key-value database](https://en.wikipedia.org/wiki/Key–value_database) (Distributed Hashing)
 > - Non-relational database that uses a simple key-value method.
 > - Ex: Redis

 # special considerations
 1. versioning
 2. portability
 3. human-readable
 4. partial loading
 5. random access
 6. error handling
 7. learning curve for new developer
 8. customize memory allocation (memory pool)

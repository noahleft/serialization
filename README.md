# Serialization Techniques Comparsion
 What is serailization?

 the definition of serialization from wiki:
 
 >[Serialization](https://en.wikipedia.org/wiki/Serialization) is the process of translating a data structure or object state into a format that can be stored  (for example, in a file or memory data buffer) or transmitted (for example, across a computer network) and reconstructed later (possibly in a different computer environment).
 
 In short, serialization is to save-and-restore the program data in a proper way. With given data entry, the program would serialize the data to the disk.
 
 A general study is Boost Serialization which is peer-reviewed C++ library.
 > Features of Boost Serialization:
 > - It meets C++'s zero-overhead principle (a.k.a don't pay for what you don't use).
 > - Provides flexibility to customize everything.
 
 In the other side, Protocol Buffer which is Google's serialization library.
 > Features of Google ProtoBuf:
 > - Requires IDL model abstraction between target data and serialized format.
 > - Provides forward and backward compatible natively between IDL and Serialized format.

 The following table shows the comparsion on different techniques.

 symbol meanings:
 - ✅ Pros:    this approach can natively support it.
 - ❌ Cons:    this approach can not handle it well. Require significant effect.
 - ⚠️ Neutral: this approach needs some extra handling. But it's do-able in most cases.

|                    | Boost Serialization | Code Generation| Google ProtoBuf | ProtoBuf+Tracking |Relational Database|
| ------------------ | ------------- | ------------- | ------------- | ------------- | ------------- |
| Engine             | Boost         | Boost         | ProtoBuf      | ProtoBuf      | SQLite3       |
| Pointer Referencing| ✅ Natively   | ✅ Natively | ❌ | ⚠️ Indexing |⚠️ Indexing |
| Cross Versioning.  | ⚠️             | ❌ | ✅ Natively |✅ Natively |✅ Natively |
| Learning Curve.    | ❌            | ✅| ✅ | ❌ | ✅ |
| Low-level Support. | ✅            |  ✅            |  ⚠️            |  ⚠️            |  ❌            | 
 
 1. Boost Serialization: (serialize directly)
 > - Define the serialize function on the target data.
 > 1. ✅ pointer referencing: object tracking on the pointer address
 > 2. ⚠️ cross version: user need to handle the version migration on serialize function
 > 3. ❌ learning curve: foreach header change, the developer needs to handle the serialization parts.
 >> In general development flow, the database is controlled by a small group of developers.
 >> For each definition changes, it will require database expert to enhance the corresponding changes.
 > 4. ⚠️ inheritance: user need to export the base-derived relationship
 > 5. ✅ memory consumption: serailze *directly*, so no extra memory required.

 2. Code Generation (Implemented by Boost Serialization + Lex/Yacc code generation):
 > - Use header file as IDL model to generate the serialize function on the target data.
 > 1. ✅ pointer referencing: object tracking on the pointer address
 > 2. ❌ cross version: user need to handle the version migration on serialize function
 > 3. ✅ learning curve: with well-defined code generation, no extra work needed.
 >> In general, code generation would help RD to auto-gen the serialization function. 
 >> But it would cause the side-effect on forward/backward compatible.
 > 4. ⚠️ inheritance: user need to export the base-derived relationship
 > 5. ✅ memory consumption: serailze *directly*, so no extra memory required.
 
 3. Google Protocol Buffer: (IDL based)
 > - Define the IDL model in ProtoBuf format. Then, translate the target data to the IDL model.
 > 1. ❌ pointer referencing: user need to record the relationship on IDL model. A general solution is indexing.
 > 2. ✅ cross version: protocl buffer support the cross version natively
 > 3. ✅ learning curve: with well-defined IDL model, no extra work needed.
 > 4. ⚠️ inheritance: user need to record the base-derived relationship on IDL model
 > 5. ❌ memory consumption: Extra O(n) space required. ProtoBuf needs to **translate** the target data to required IDL model.
 >> The modification on the generated code is not recommended in ProtoBuf documentation.

 4. ProtoBuf+Tracking (Implemented by Indexing shared object)
 > - Define the IDL model in ProtoBuf format. **And indexing shared object by developer.** Then, translate the target data to the IDL model.
 > 1. ⚠️ pointer referencing: the relationship is indexed as shared object on IDL model.
 > 2. ✅ cross version: protocl buffer support the cross version natively
 > 3. ❌ learning curve: indexing requires expert maintenace. Especially on the question "how many shared objects in your program?"
 > 4. ⚠️ inheritance: user need to record the base-derived relationship on IDL model
 > 5. ❌ memory consumption: Extra O(n) space required. ProtoBuf needs to **translate** the target data to required IDL model.
 >> The modification on the generated code is not recommended in ProtoBuf documentation.

 5. [Relational Database](https://en.wikipedia.org/wiki/Relational_database) (Implemented with Indexing shared object)
 > - Abstract the data to relational model. **And indexing shared object by developer.** Then, translate the target data to the IDL model.
 > - Use traditional CRUD operations to store the data. Ex: SQLite
 > 1. ⚠️ pointer referencing: the relationship is indexed as shared object on IDL model.
 > 2. ✅ cross version: relational data model support the cross version natively
 > 3. ✅ learning curve: indexing requires expert maintenace. But the relational database is common in many different area.
 > 4. ⚠️ inheritance: user need to record the base-derived relationship on IDL model
 > 5. ⚠️ memory consumption: **Stepwise** translation does not require extra memory.

# demo example

[Have a look on the example data.](data/)

```C++
class bus_route
{
public:
#pragma bus_stop_detail
    std::vector<bus_stop*> routes;
    std::string route_name;       // add a string "route_name" as header change
};
```
1. The modification for Boost Serialization,
```C++
void serialize(Archive & ar, bus_route & obj, const unsigned int version) {
    ar.template register_type<bus_stop_detail>();
    ar & obj.routes;
    ar & obj.route_name;          // corresponding serialization code
}
 ```
2. The modification for Code Generation
> Serialization code auto-generation. No modification required.

3. The modification for ProtoBuf
```ProtoBuf
message BusRoute {
    repeated BusStop routes = 1;
    optional string route_name = 2;// corresponding ProtoBuf IDL model
}
```
```C++
static void translate_bus_route(data::BusRoute *model, bus_route *data) {
    model->set_route_name(data->route_name); // corresponding bridge between data and IDL
    ...
}
static bus_route* restore_bus_route(data::BusRoute *model) {
    data->route_name = model->route_name(); // corresponding bridge between data and IDL
    ...
}
```
4. The modification for ProtoBuf + Object Tracking
> The same as ProtoBuf.

5. The modification for Relational Database
> Define the **new** column on current database schema
```SQLite
CREATE TABLE BUS_ROUTE(
...
NAME TEXT
);
```
```C++
void sql_interface::serialize() {
  sql << "INSERT INTO BUS_ROUTE (ID, NAME, ROUTE) VALUES ("
  ...
  ... /*need to modify the corrseponding sql string*/
}

void br_callback(...) {
  ...
  br->route_name = string(argv[1]); /*error handling if cross version required.*/
  ...
}
```

# related approach
 1. [application checkpointing](https://en.wikipedia.org/wiki/Application_checkpointing) (Process snapshot)
 > - Check point the process to disk and restart later. 
 > - Ex: Distributed MultiThreaded CheckPointing (DMTCP), Checkpoint/Restore In Userspace (CRIU), Berkeley Lab Checkpoint/Restart (BCLR)
 2. [key-value database](https://en.wikipedia.org/wiki/Key–value_database) (Distributed Hashing)
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

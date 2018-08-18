```puml
skinparam packageStyle rectangle

abstract class Generator {
  #List<UpdatePair> update_chain
  #void merge_update_chain(List<UpdatePair>)
  ~{abstract} GenElement* get_element(Json)
  ~{abstract} Generator* get_generator(Json)
  ~void appoint()
  ~void hello()
  ~void goodbye()
  ~List<UodatePair> get_update_chain()
}

class UpdatePair.GenElement {
  ~GenElement()
  -{static} int instance_count
  -int ID
  -int n_remain
  -Json data
  -Set<Str> datakeys
  -omp_lock_t omp_lock
  ~GenElement* get_element(Json)
  ~Generator* get_generator(Json)
  ~void increment_remain()
  ~void decrement_remain()
  ~void update_data(Updater*)
  +GenElement* append_updater(Updater*)
  +Json get_data()
  +Set<Str> get_keys()
  +ArrayXi get_1d_int(Str)
  +ArrayXd get_1d_double(Str)
  +ArrayXXi get_2d_int(List<Str>)
  +ArrayXXd get_2d_double(List<Str>)

  +GenElement* Element(Updater*)
}

Generator <|-- UpdatePair.GenElement

class GenList {
  ~GenList(List<Generator*>)
  -List<Generator*> generator_list
  ~GenElement* get_element(Json)
  ~Generator* get_generator(Json)
  ~int get_length()
}

Generator <|-- GenList

class GenDict {
  ~GenDict(Dict<Str,Generator*>)
  -Dict<Str,Generator*> generator_dict
  ~GenElement* get_element(Json)
  ~Generator* get_generator(Json)
  ~Set<Str> get_keys()
}

Generator <|-- GenDict

abstract class UpdatePair.Updater {
  -Set<int> dataid_blacklist
  -omp_lock_t omp_lock
  #Generator* ext_generator
  #{abstract} void compute_impl(Json, Set<Str>)
  #bool check_blacklist(int)
  ~{abstract} void compute(Json, Set<Str>, int)
  ~void remove_from_blacklist(int)
  ~Generator* get_ext_generator()
}

abstract class Adder {
  ~void compute(Json, Set<Str>, int)
}

UpdatePair.Updater <|-- Adder

class AddMap {
  +AddMap(Str, Str, Dict<Json,Json>)
  +AddMap(Str, Str, Dict<Json,Json>, bool)
  -bool overwrite
  -Str key_ref
  -Str key_new
  -Dict<Json,Json> mapping
  #void compute_impl(Json, Set<Str>)
}

Adder <|-- AddMap

class AddRename {
  +AddRename(Str, Str)
  +AddRename(Str, Str, bool)
  -bool overwrite
  -Str key_old
  -Str key_new
  #void compute_impl(Json, Set<Str>)
}

Adder <|-- AddRename

class AddWrappedPositions {
  +AddWrappedPositions(GenElement*)
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddWrappedPositions

class AddCoMPositions {
  +AddCoMPositions(GenElement*)
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddCoMPositions

class AddInertiaMoment {
  +AddInertiaMoment(GenElement*)
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddInertiaMoment

class AddGyrationRadius {
  +AddGyrationRadius()
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddGyrationRadius

class AddMolecularOrientation {
  +AddMolecularOrientation()
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddMolecularOrientation

abstract class Starter {
  ~void compute(Json, Set<Str>, int)
}

UpdatePair.Updater <|-- Starter

class StaCustom {
  +StaCustom(Json)
  -Json json
  -Set<Str> jsonkeys
  #void compute_impl(Json, Set<Str>)
}

Starter <|-- StaCustom

abstract class StaDump {
  #int timestep
  #Str filepath
}

Starter <|-- StaDump

class StaDumpAtoms {
  +StaDumpAtoms(Str, int)
  -List<bool> get_is_int_vector(Str)
  #void compute_impl(Json, Set<Str>)
}

StaDump <|-- StaDumpAtoms

class StaDumpBox {
  +StaDumpBox(Str, int)
  #void compute_impl(Json, Set<Str>)
}

StaDump <|-- StaDumpBox

class StaMolecules {
  +StaMolecules(GenElement*)
  #void compute_impl(Json, Set<Str>)
}

Starter <|-- StaMolecules

abstract class Filter {
  ~void compute(Json, Set<Str>, int)
}

UpdatePair.Updater <|-- Filter

class FilSet {
  +FilSet(Dict<Str,Set<Json>>)
  +FilSet(GenElement*, Dict<Str,Set<Json>>)
  -Dict<Str,Set<Json>> value_sets
  #void compute_impl(Json, Set<Str>)
}

Filter <|-- FilSet

class FilComparison {
  +FilComparison(tuple<Str,Str,Json>)
  +FilComparison(List<tuple<Str,Str,Json>>)
  +FilComparison(GenElement*, tuple<Str,Str,Json>)
  +FilComparison(GenElement*, List<tuple<Str,Str,Json>>)
  -List<pair<Str,function>> compare_funcs
  -function make_lambda(Str, Json)
  -List<pair<Str,function>> convert_to_funcs(List<tuple<Str,Str,Json>>)
  #void compute_impl(Json, Set<Str>)
}

Filter <|-- FilComparison

abstract class Processor {
  -int i_generator
  #int n_generators
  #List<Generators*> generators
  #{abstract} void run_impl(int)
  #void register_generators(GenElement*)
  #void register_generators(GenList*)
  #void register_generators(GenDict*)
  #void register_generators(List<GenElement*>)
  #void register_generators(List<GenList*>)
  #void register_generators(List<GenDict*>)
  ~void prepare()
  ~void finish()
  ~bool run()
}

class ProData {
  +ProData(GenElement*)
  +ProData(List<GenElement*>)
  -Set<Str> selected_keys
  -List<Json> results
  #void run_impl(int)
  ~void prepare()
  +void select(py::args)
  +List<Json> get_results()
}

Processor <|-- ProData

class ProValueArray {
  +ProValueArray(GenElement*)
  +ProValueArray(List<GenElement*>)
  -Set<Str> selected_keys
  -Dict<Str,ArrayXXd> results
  -Dict<Str,List<RowArrayXd>> results_tmp
  #void run_impl(int)
  ~void prepare()
  ~void finish()
  +void select(py::args)
  +Dict<Str,ArrayXXd> get_results()
}

Processor <|-- ProValueArray

abstract class Invoker {
  #int n_processors
  #List<Processor*> processors
  #{abstract} void execute_impl()
  +void execute()
}

class InvoOMP {
  +InvOMP(Processor*)
  +InvOMP(List<Processor*>)
  #void execute_impl()
}

Invoker <|-- InvoOMP

Generator "*" o---- "*" UpdatePair

Processor "*" o---- "*" Generator
Invoker "*" o---- "*" Processor

UpdatePair.GenElement .left> UpdatePair.Updater : use
```
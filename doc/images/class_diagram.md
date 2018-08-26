```puml
skinparam packageStyle rectangle

abstract class Generator {
  #Vec<UpdatePair> update_chain
  #void merge_update_chain(Vec<UpdatePair>)
  ~{abstract} Element* get_element(Json)
  ~{abstract} Generator* get_generator(Json)
  ~void appoint()
  ~void hello()
  ~void goodbye()
  ~Vec<UodatePair> get_update_chain()
}

class UpdatePair.Element {
  ~Element()
  -{static} int instance_count
  -int dataid
  -int n_remain
  -Json data
  -Set<Str> datakeys
  -omp_lock_t omp_lock
  ~Element* get_element(Json)
  ~Generator* get_generator(Json)
  ~void increment_remain()
  ~void decrement_remain()
  ~void update_data(Updater*)
  +Element* append_updater(Updater*)
  +Json get_data()
  +Set<Str> get_keys()
  +ArrayXi get_1d_int(Str)
  +ArrayXd get_1d_double(Str)
  +ArrayXXi get_2d_int(Vec<Str>)
  +ArrayXXd get_2d_double(Vec<Str>)

  +Element* create(Updater*)
}

Generator <|-- UpdatePair.Element

class GenList {
  ~GenList(Vec<Generator*>)
  -Vec<Generator*> generator_list
  ~Element* get_element(Json)
  ~Generator* get_generator(Json)
  ~int get_length()
}

Generator <|-- GenList

class GenDict {
  ~GenDict(Map<Str,Generator*>)
  -Map<Str,Generator*> generator_dict
  ~Element* get_element(Json)
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
  +AddMap(Str, Str, Map<Json,Json>)
  -bool overwrite
  -Str key_ref
  -Str key_new
  -Map<Json,Json> mapping
  #void compute_impl(Json, Set<Str>)
  +AddMap* overwrite(bool)
}

Adder <|-- AddMap

class AddRename {
  +AddRename(Str, Str)
  -bool overwrite
  -Str key_old
  -Str key_new
  #void compute_impl(Json, Set<Str>)
  +AddRename* overwrite(bool)
}

Adder <|-- AddRename

class AddWrappedPositions {
  +AddWrappedPositions(Element*)
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddWrappedPositions

class AddCoMPositions {
  +AddCoMPositions(Element*)
  -compute_with_weights(Json, Element*)
  -compute_without_weights(Json, Element*)
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddCoMPositions

class AddInertiaMoment {
  +AddInertiaMoment(Element*)
  -compute_with_weights(Json, Element*)
  -compute_without_weights(Json, Element*)
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddInertiaMoment

class AddGyrationRadius {
  +AddGyrationRadius()
  -bool add_squared
  -bool add_sqrted
  #void compute_impl(Json, Set<Str>)
  +AddGyrationRadius* with_squared(bool)
  +AddGyrationRadius* without_sqrted(bool)
}

Adder <|---- AddGyrationRadius

class AddMolecularOrientation {
  +AddMolecularOrientation()
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddMolecularOrientation

class AddChildIDs {
  +AddChildIDs(Element*, Str, Str)
  -Str child_name
  -Str key_for_parent_id
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddChildIDs

class AddSpecialBonds {
  +AddSpecialBonds(Element*, Vec<Vec<int>>)
  +AddSpecialBonds(Element*, Map<int,Vec<Vec<int>>>)
  -Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol
  #void compute_impl(Json, Set<Str>)
}

Adder <|---- AddSpecialBonds

abstract class Starter {
  -void sort_by_id(Json)
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
  -Vec<bool> make_is_int_vector(Str)
  #void compute_impl(Json, Set<Str>)
}

StaDump <|-- StaDumpAtoms

class StaDumpBox {
  +StaDumpBox(Str, int)
  #void compute_impl(Json, Set<Str>)
}

StaDump <|-- StaDumpBox

class StaMolecules {
  +StaMolecules(Element*)
  #void compute_impl(Json, Set<Str>)
}

Starter <|-- StaMolecules

class StaBeads {
  +StaBeads(Element*, Vec<Json>)
  +StaBeads(Element*, Map<int,Vec<Json>>)
  -Map<int,Vec<Json>> mol_type_to_abst_beads
  -std::pair<bool,bool> check_mol_type_to_abst_beads()
  #void compute_impl(Json, Set<Str>)
}

Starter <|-- StaBeads

abstract class Filter {
  ~void compute(Json, Set<Str>, int)
}

UpdatePair.Updater <|-- Filter

class FilSet {
  +FilSet(Map<Str,Set<Json>>)
  +FilSet(Element*, Map<Str,Set<Json>>)
  -Map<Str,Set<Json>> value_sets
  #void compute_impl(Json, Set<Str>)
}

Filter <|-- FilSet

class FilComparison {
  +FilComparison(tuple<Str,Str,Json>)
  +FilComparison(Vec<tuple<Str,Str,Json>>)
  +FilComparison(Element*, tuple<Str,Str,Json>)
  +FilComparison(Element*, Vec<tuple<Str,Str,Json>>)
  -Vec<tuple<Str,Str,Json>> comparisons
  -function make_lambda(Str, Json)
  -Vec<pair<Str,function>> convert_to_funcs(Vec<tuple<Str,Str,Json>>)
  #void compute_impl(Json, Set<Str>)
}

Filter <|-- FilComparison

abstract class Processor {
  -int i_generator
  #int n_generators
  #Vec<Generators*> generators
  #{abstract} void run_impl(int)
  #void register_generator(Element*)
  #void register_generator(GenList*)
  #void register_generator(GenDict*)
  #void register_generators(Vec<Element*>)
  #void register_generators(Vec<GenList*>)
  #void register_generators(Vec<GenDict*>)
  ~void prepare()
  ~void finish()
  ~bool run()
}

class ProData {
  +ProData(Element*)
  +ProData(Vec<Element*>)
  -Vec<Str> selected_keys
  -Vec<Json> results
  #void run_impl(int)
  ~void prepare()
  +void select(py::args)
  +Vec<Json> get_results()
}

Processor <|-- ProData

class ProValueArray {
  +ProValueArray(Element*)
  +ProValueArray(Vec<Element*>)
  -Vec<Str> selected_keys
  -Map<Str,ArrayXXd> results
  -Map<Str,Vec<RowArrayXd>> results_tmp
  #void run_impl(int)
  ~void prepare()
  ~void finish()
  +void select(py::args)
  +Map<Str,ArrayXXd> get_results()
}

Processor <|-- ProValueArray

class ProThicknessProfile {
  +ProThicknessProfile(Element*, Element*)
  +ProThicknessProfile(Vec<pair<Element*,Element*>>)
  -int nx
  -int ny
  -bool shift_half
  -double offset
  -Vec<Json> conditions
  -Vec<ArrayXXd> profiles
  #void run_impl(int)
  ~void prepare()
  +void set_grid(int, int)
  +void set_offset(double)
  +void shift_half_delta(bool)
  +Vec<Json> get_conditions()
  +Vec<ArrayXXd> get_profiles()
}

Processor <|-- ProThicknessProfile

class ProRadialDistributionFunction {
  +ProRadialDistributionFunction(Element*, Element*)
  +ProRadialDistributionFunction(Vec<pair<Element*,Element*>>)
  -int n_bins
  -double bin_width
  -bool bin_from_r
  -bool beyond_half
  -ArrayXd rdf
  -Vec<ArrayXd> rdf_traj
  -Vec<double> density_traj
  -Vec<ArrayXd> number_distribution_traj
  #void run_impl(int)
  ~void prepare()
  ~void finish()
  +void set_bin(double, int)
  +void bin_from_r_to_r_plus_dr(bool)
  +void beyond_half_box_length(bool)
  +ArrayXd get_r_axis()
  +ArrayXd get_rdf()
  +Vec<ArrayXd> get_rdf_traj()
}

Processor <|-- ProRadialDistributionFunction

class ProDistanceInMolecule {
  +ProDistanceInMolecule(Element*, Element*)
  +ProDistanceInMolecule(Vec<pair<Element*,Element*>>)
  -int index1_in_mol
  -int index2_in_mol
  -int target_moltype
  -bool do_sqrt
  -Vec<RowArrayXd> distance2_traj
  -ArrayXXd distance_array
  -ArrayXXd distance2_array
  #void run_impl(int)
  ~void prepare()
  ~void finish()
  +void set_indices(int, int)
  +void set_moltype(int)
  +void compute_sqrt(bool)
  +ArrayXXd get_distance_array()
  +ArrayXXd get_distance2_array()
}

Processor <|-- ProDistanceInMolecule

class ProMeanSquareDisplacement {
  +ProMeanSquareDisplacement(Vec<Element*>)
  -bool drift_correction
  -Vec<bool> dimension
  -ArrayXXd initial_rs
  -Vec<RowArrayXd> displacement2_traj
  -ArrayXXd displacement2_array
  -ArrayXd mean_square_displacement
  #void run_impl(int)
  ~void prepare()
  ~void finish()
  +void set_dimension(bool, bool, bool)
  +void without_drift_correction(bool)
  +ArrayXXd get_displacement2_array()
  +ArrayXd get_mean_square_displacement()
}

Processor <|-- ProMeanSquareDisplacement

abstract class Invoker {
  #int n_processors
  #Vec<Processor*> processors
  #{abstract} void execute_impl()
  +void execute()
}

class InvoOMP {
  +InvOMP(Processor*)
  +InvOMP(Vec<Processor*>)
  #void execute_impl()
}

Invoker <|-- InvoOMP

class KeyChecker {
  ~KeyChecker()
  #bool check_key(Set<Str>, Str, Str)
  #bool check_key(Set<Str>, Vec<Str>, Str)
  #bool check_key(Element*, Str)
  #bool check_key(Element*, Vec<Str>)
  #Str get_my_class_name()
}

KeyChecker <|---- UpdatePair.Updater
KeyChecker <|---- Processor

Generator "*" o---- "*" UpdatePair

Processor "*" o---- "*" Generator
Invoker "*" o---- "*" Processor

UpdatePair.Element .left> UpdatePair.Updater : use
```
# Pointers/References

## Raw Pointers

- A **pointer** (which is also a variable) contains an address in memory and is allocated on the heap.

  - For the below example, *ptr* will point at the address in which *var* is stored at with value: 08 00 00 00 (since int is 4 bytes)

- We can **dereference** a pointer by adding a * before it in order to overwrite it.

  ```cpp
  int main() {
      int var = 8;
      int* ptr = &var;
      *ptr = 10; // overwrite value at &var from 8 to 10
  }
  ```

- We can also **allocate** certain amounts of memory and then set then with variables.

  ```cpp
  int main() {
      char* buffer = new char[8]; // char is 1 byte, so 8 chars -> 8 bytes of data in memory
      memset(buffer, 0, 8); // fills memory at buffer with: 00 00 00 00 00 00 00 00
      char** ptr = &buffer; // points to the address of the memory which holds the pointer to buffer
      delete[] buffer; // delete data from heap when done
  }
  ```

- A **reference** is a way for us to refer to an existing variable (does not actually exist).

- We can change variables in function by **passing a pointer** as parameters

  - Note that for the below function, there is no return value. So by passing the address in memory, we are directly changing the variable instead of returning a new value.
  - We have to pass the address of a into the function and dereference it within the function otherwise we would be incrementing the actual memory address instead of the value.

  ```cpp
  void Increment(int* value) {
      (*value)++; // dereference the value 
  }
  
  int main() {
      int a = 5;
      int& ref = a; // think of this as "ref is a"
      ref = 2; // now we have a = 2
      Increment(&a); // currently a = 2
      LOG(a); // 3
  }
  ```

- We can do this even easier by **passing a reference** as a parameter instead of a pointer.

  ```cpp
  void Increment(int& value) {
      value++; // dereference the value 
  }
  
  int main() {
      int a = 5;
      Increment(a); // currently a = 5
      LOG(a); // 6
  }
  ```

- NOTE: you CANNOT reassign references after they are assigned (this will just overwrite whatever value the reference refers to with the new value)

  ```cpp
  int main() {
      // Incorrect way
      int a = 5;
      int b = 6;
      int& ref = a;
      ref = b; // we now have: a = 6, b = 6
      
      // Correct way
      int c = 7;
      int d = 8;
      int* ref = &a; // ref is now a pointer
      *ref = 2; // we now have c = 2
      ref = &b; // ref now points to b instead of a
      *ref = 1; // we now have d = 2
  }
  ```

## Smart Pointers

- These are ways to automate memory allocation on the heap and deleting them afterwards.

  - When you call *new* you no longer need to call *delete*.

- A **unique pointer** is when you don't want to share it with any other parts of the code (cannot be copied or sent to functions).

- A **shared pointer** works by reference counting (keep track of number of references to the pointer) and is deleted when the count equals 0.

- A **weak pointer** can be used with a *shared pointer* to copy a pointer but not increase the reference count.

  ```cpp
  #include <memory>
  
  class Entity() {
      //...
  };
  
  int main() {
      {
          std::unique_ptr<Entity> e = std::make_unique<Entity>(); // unique pointer
      	e->Print();
      } // e will be deleted automatically after leaving this scope
      
      {
          std::shared_ptr<Entity> e0;
      	{
          	std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
              std::weak_ptr<Entity> weakEntity = sharedEntity;
          	e0 = sharedEntity;
      	} // sharedEntity pointer will be deleted, but e0 will still point to address (ref count = 1)
      } // e0 will be deleted, now the destuctor is called (ref count = 0)
  }
  ```



# Loops

## Ternary Operators

- The **ternary operator** allows if/else statements to be reduced into a single line of code.

  - Note: these operators can be nested within each other (as well as including logical operators) - try to avoid this though.

  ```cpp
  static int s_Level = 1;
  static int s_Speed = 2;
  
  int main() {   
      s_Speed = s_Level > 5 ? 10 : 5;
      s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5; // [if level > 5 then] (if level > 10 then 15 else 10) [else 5]
  }
  ```







# Objected Oriented Programming

## Classes/Structs

- Classes must be specified on who can access them (by default this is private). 

- The only difference between a **struct** and a class is that a struct is public by default.

  - A struct could be used when the data is less complicated and needs simple manipulation (i.e. a  vector struct).

  ```cpp
  class Log
  {
  public: // public variables
      const int LogLevelError = 0;
      const int LogLevelWarning = 1;
      const int LogLevelInfo = 2;
  private: // not accessible outside of the class
      int m_LogLevel = LogLevelInfo; // assign initial value
  public: // public methods
      void SetLevel(int level) {
          m_LogLevel = level; // set private variable
      }
      void Warn(const char* message) {
          std::cout << "[WARNING]:" << message << std::endl;
      }
  };
  
  int main() {
      Log log;
      log.SetLevel(log.LogLevelWarning); // set to LogLevelWarning (value of 1)
      log.Warn("Testing");       
  }
  ```

- **Visibility** determines who can access variables/methods within a class.
  - Private (class default) - only within the class can access the variables/functions (note: a *friend* can access private members of class).
  - Protected - the class and any subclasses can access the variables/functions (but not outside of the classes).
  - Public (struct default) - variables/functions can be accessed both within classes and outside of them.

  

## Static

- Static variables are only accessible within the given cpp file and cannot be accessed outside of it (not linked, think of this as a private variable).

  - This can also be done for functions so that they are only used within the defined cpp file.
  - We want to use this when we don't need variables to be global.

  ```cpp
  static int s_Variable = 5;
  
  static void Function() {
      // code here...
  }
  ```

### Static Classes/Structs

- For **static variables** within classes, there is only one variable shared between all class/struct instances.

- **Static methods** can't access non-static variables. 

  ```cpp
  struct Entity {
      static int x, y;
      static void Print() std::cout << x << ", " << y << std::endl;
  }
  
  int Entity::x; // define static variables
  int Entity::y; // define static variables
  
  int main() {  
      Entity::x = 5;
      Entity::y = 8;
      Entity::Print();
  }
  ```

### Local Static

- A **local static variable** within a function can be used throughout the lifetime of the program, but cannot be changed outside of the code. Think of this as storing the variable in memory but only using it within the scope of the function (can't be accessed globally).

  ```cpp
  void Function() {
      static int i = 0;
      i++; 
      std::cout << i << std:;endl;
  }
  ```



## ENUMS

- This is a way to easily define values that are all integers.

- By default, first value in enum list is 0, and is then incremented by 1 as we go through. These can also be set manually.

  ```cpp
  enum Example : char { // set data type (8-bit)
      A=2, B, C // 2, 3, 4
  };
  
  int main() {
      Example value = B; // = 3
  }
  ```



##  Constructors/Destructors

- By default, the **constructor** is empty. We define the constructor with the same name as the class.

- We can also have parameters passed to the constructor when initializing a class instance.

- A **destructor** is called whenever a class object is deleted and is defined with a ~.

  - Below, since the object is created on the *stack* it is automatically destroyed.

  ```cpp
  class Entity {
  public:
      float X, Y;
      Entity(float x, float y) { // constructor
         std::cout << "Created Entity!" << std::endl;
         X = x;
         Y = y;
      }
      ~Entity() {
          std::cout << "Destroyed Entity!" << std::endl;
      }
      void Print() std::cout << X << ", " << Y << std::endl;
  };
  
  int main() {
      Entity e(10.0f, 5.0f);
      e.Print();
  }
  ```

### Explicit

- The **explicit keyword** is used to make sure that a constructor must be called and cannot use *implicit conversion*.

  ```cpp
  class Entity {
  private:
      std::string m_Name;
      int m_Age;
  public:
      explicit Entity(const std::string& name) : m_name(name), m_Age(-1) {} // constructor #1
      explicit Entity(int age) : m_name("Unknown"), m_Age(age) {} // constructor #2
      const std::string& GetName() const { return m_Name; }
  };
  
  int main() {
      Entity a = "Test"; // won't work since "explicit"
      Entity b = 22; // won't work since "explicit"
  }
  ```

  

## Member Initializer Lists

- In the constructor, instead of listing variables on each line we can initialize the variables in a single line.

  ```cpp
  class Entity {
  private:
      std::string m_Name;
  public:
      Entity() : m_name("Unknown") { } // default constructor
      Entity(const std::string& name) : m_name(name) { }
      const std::string& GetName() const { return m_Name; }
  };
  ```

  

## Inheritance

- This allows us to create a **parent class** with common code, and create **child classes** that inherit this code and has its own as well.

  ```cpp
  class Entity { // parent class
  public:
      float X, Y;
      void Move(float xa, float ya) {
          X += xa;
          Y += ya;
      }
  };
  
  class Player : public Entity { // child class
  public:
      const char* Name;
      void PrintName() std::cout << Name << std::endl;
  };
  
  int main() {
      Player player;
      player.Move(5,5);
      player.X = 2;
  }
  ```



## Virtual Functions

- **Virtual functions** allow us to override methods in subclasses (child function can override parents function).

- In the *base class* we can specify functions that we want to override with the **virtual** keyword, and in the *subclass* we pass the **override** keyword within our function we want to override.

  - Virtual functions have 2 runtime costs: (1) - additional memory needed to store vtable, (2) - have to go through vtable every time we call function.

  ```cpp
  #include <string>
  
  class Entity {
  public:
      virtual std::string GetName() { return "Entity"; }
  };
  
  class Player : public Entity {
  private:
      std::string m_Name;
  public:
      std::string GetName() override { return m_Name; }
  };
  ```

### Interfaces (Pure VFs)

- **Pure Virtual Functions** allow us to define a function in the base class without having to write it, and then implement the functions within the subclasses. This may be when we don't need a default for a given function.

- This is called an **interface class** where we only define objects we need for subclasses (but don't instantiate the class ever - template class).

  ```cpp
  class Printable { // template class (interface)
  public:
      virtual std::string GetClassName() = 0; // pure virtual function
  };
  
  class Entity : public Printable {
  public:
      virtual std::string GetName() { return "Entity"; }; 
      std::string GetClassName() override { return "Entity"; }
  };
  
  class Player : public Entity { // inherites both Entity & Printable class
  private:
      std::string m_Name;
  public:
      std::string GetName() override { return m_Name; }
      std::string GetClassName() override { return "Player"; }
  };
  ```

### Virtual Destructors

- **Virtual Destructors** are used when we are using *inheritance* and need to call both destructors (but the code might not be).

  - This can cause memory leaks if we allocate memory in the constructor but don't call the destructor to free it up.

  ```cpp
  class Base {
  public:
      Base() { std::cout << "Base Constructor\n"; }
      virtual ~Base() { std::cout << "Base Destructor\n"; }
  };
  
  class Derived: public Base {
  public:
      Derived() { m_Array = new int[5]; std::cout << "Derived Constructor\n"; }
      ~Derived() { delete[] m_Array; std::cout << "Derived Destructor\n"; }
  private:
      int* m_Array;
  };
  
  int main() {
      Base* base = new Base(); // calls base constructor
      delete base; // calls base destructor
      Derived* dervied = new Derived(); // calls base/dervied constructor
      delete derived(); // calls base/dervied destructor
      Base* poly = new Derived(); // calls base/dervied constructor
      delete poly; // without "virtual" in ~Base(), would only call base destructor and not derived
  }
  ```




# Arrays

- An **array** is just a pointer to a specified size block of memory that has been allocated.

  ```cpp
  int main() {
      // Stack (destroyed automatically)
      int example[5];
      int* ptr = example; // ptr contains address of example
      example[2] = 5;
      *(ptr + 2) = 6; // pointer arithmetic (adds 2*4 since int is 4 bytes)
      int count = sizeof(example) / sizeof(int); // (5 elements * 4 bytes) / (4 bytes) - only works on stack arrays
      
      // Heap (need to delete)
      int* another = new int[5];
      delete[] another;
  }
  ```

## Static Arrays

- In *C++ 11* there is a library for **standard arrays**, which are predetermined size and cannot be changed after declaration (constant) - stored on the stack.

  - Note that this has a *.size()* method which returns the length of the array.

- Using standard arrays is determined by the problem you are working on (speed, bounds checking, etc.).

  ```cpp
  #include <array>
  
  int main() {
      std::array<int, 5> example;
  }
  ```

## Dynamic Arrays (vector)

- A **dynamic array** does not need to have a specified size (you can add elements after declaration). 

- Passing these dynamic arrays to functions should be **by reference** to avoid copying the array.

- **Optimizing** the use of dynamic arrays:

  - using *reserve()* allows us to set aside enough memory to add a specified number of elements to (reduces the number of copies we have to make in half).
  - using *emplace_back()* instead of *push_back()* allows us to create objects within arrays rather than creating in the main code, and then copying into the array (this reduces the number of total copies down to 0 in below code).

  ```cpp
  #include <vector>
  
  struct Vertex {
      float x,y,z;
      Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
      Vertex(const Vertex& vertex) : x(vertex.x), y(vertex.y), z(vertex(.z)) { // copy constructor
          std::cout << "Copied." << std:endl;
      }
  };
  
  int main() {
      std::vector<Vertex> vertices; // initialize empty arry of vertex class
      vertices.reserve(2); // OPTIMIZE STEP - set aside enough memory for below elements (cuts number of copies in half)
      vertices.emplace_back(1,2,3); // OPTIMIZE STEP - push_back() creates copy, emplace creats object in array
      vertices.emplace_back(4,5,6); // OPTIMIZE STEP - push_back() creates copy, emplace creats object in array
      
      for(Vertex& v : vertices)
          std::cout << v << std::endl; // note that << operator is overloaded in Vertex class
      
      vertices.erase(vertices.begin() + 1); // delete the second element
      vertices.clear(); // delete all elements and set size back to 0
  }
  ```

## Multidimensional Arrays

- **2D arrays**: in the definition, we create a pointer to an int pointer. Below, we allocate 20 bytes of memory (5 int pointers, 4 bytes each).

  - We can then set each of these int pointers to then point at an array, gives us our "array of 5 arrays", which is actually just an array of pointers to arrays.
  
- When **deleting** these arrays, we have to iterate over the outer array and delete each inner array.

  ```cpp
  int main() {
      int** a2d = new int*[5]; 
      for (int i = 0; i < 5; i++) // create array pointers at each index
          a2d[i] = new int[5];
      for (int i = 0; i < 5; i++) // delete array pointers at each index
          delete[] a2d[i];
      delete[] a2d; // delete outer array
  }
  ```


## Sorting

- We can use the *std library* to sort an type of iterator we pass into it (default is in ascending order, compares by "a < b").

  ```cpp
  #include <vector>
  #include <sort>
  
  int main() {
      std::vector<int> value = { 3, 4, 1, 4, 2 };
      std::sort(values.begin(), values.end(), [](int a, int b) 
                {
                    if (a == 1) // keep value 1 at the end of the list
                        return false;
                    if (b == 1)
                        return true;
                    return a > b; // sort in ascending order
                });
      
      for (int value : values)
          std::cout << value << std::endl;
  }
  ```



# Strings

- The *char* data type is 1 byte, and a **string** is just an array of characters.

  - Strings end at the *null terminator* (\0) 
  
- The **standard string** is a char array that comes from the *string* package.

  - The <iostream> library has a string built in, but the <string> package overloads and allows us to print to the console.

  ```cpp
  # include <string>
  
  int main() {
      const char* name = "Test"; // const isn't necessary, only when we want it to be immutable
      std::string name = "Test"; // defines as a "const char"
      std::string name2 = std::string("Test") + " #2"; // or "std::string name2 = "Test"s + " #2";"
      bool contains = name.find("st") != std::string::npos; // see if string contains something
  }
  ```


## String Views (C++17)

- The problem with strings is that *std::string* allocates memory on the heap (and this can slow down our program).

- Instead of creating a new sub string if we want to extract a piece of the original string, we can make a **std::string_view**.

  - It is a *const char\** to an existing string, along with the size of the string. Because of this, it won't allocate memory when created (lightweight).

  ```cpp
  #define STRING_VIEW 1 // use string view (to not use, change to 0)
  static uint32_t s_AllocCount = 0;
  
  void* operator new(size_t size) { // override new operator (since std::string allocates on heap)
      s_AllocCount++;
      std::cout << "Allocating " << size << " bytes\n";
      return malloc(size);
  }
  
  #if STRING_VIEW
  void PrintName(const std::string_view name) { 
      std::cout << name << std::endl;
  }
  #else
  void PrintName(const std::string& name) {
      std::cout << name << std::endl;
  }
  #endif
  
  int main() {
  #if STRING_VIEW
      std::string name = "Derek Helms"; // creates new string and allocates memory
      std::string firstName = name.substr(0,5); // creates new string and allocates memory
      std::string lastName = name.substr(6,5); // creates new string and allocates memory
  #else
      const char* name = "Derek Helms"; // no memory allocation
      std::string_view firstName(name.c_str(), 5); // create view, no memory allocation
      std::string_view firstName(name.c_str() + 6, 5); // create view, no memory allocation
  #endif
      PrintName(name);
      PrintName(firstName);
      PrintName(lastName);
  }
  ```

- A **small string** varies in sizes depending on the IDE, but in Visual Studio it is a string with less than *15 characters* (_BUF_SIZE - 1).

  - The difference is that small string get allocated on the *stack* rather than the *heap* (no need to optimize code).



# Mutable

- Marking a variable as **mutable within a class** means that const methods within a class can actually modify that variable.

- Marking a variable as **mutable for a lambda** means that variables passed by value [=] can be changed.

  ```cpp
  class Entity {
  private:
      std::string m_Name;
      mutable int m_DebugCount = 0; // make mutable in const functions
  public:
      const std::string& GetName() const { 
          m_DebugCount++; // has to be mutable
          return m_Name; 
      }
  };
  
  int main() {
      int x = 8;
      auto f[=]() mutable {
          x++; // x = 9
          std::cout << x << std::endl; // 9
      };
      f(); // calls lambda function
  }
  ```



# Creating/Instantiating Objects

- **Stack** objects have an automatic lifespan (only within the scope of their definition).

  - The stack is usually quite small, so large classes or a large number of class instances could be a problem.
  
- **Heap** objects live forever until they are freed/deleted.

  - The **new** keyword returns the memory location on the heap where the object is located, so we must assign this to a pointer.
  
  ```cpp
  using String = std::string; // define custom name for standard string
  
  class Entity {
  private:
      String m_Name;
  public:
      Entity() : m_name("Unknown") {} // default constructor
      Entity(const String& name) : m_name(name) {}
      const String& GetName() const { return m_Name; }
  };
  
  void Function() {
      Entity entity = Entity("Test"); // after leaving this function scope, object will be deleted from memory
  }
  
  int main() {
      Entity entity1; // calls default constructor (allocated on the stack)
      Entity* entity2 = new Entity("Test"); // allocated on the heap - returns location on heap where allocated
      delete entity2;
  }
  ```

## NEW

- The **new** keyword searches for a block of memory that can be used to store our object in (on the heap).

  ```cpp
  int main() {
      int* b = new int[50]; // allocates 50*4 bytes = 200 bytes
      Entity* e = new Entity(); // calls constructors and returns memory address on heap
      delete e; // calls destructor and frees memory
      delete[] b; // if used new with [] then must use delete with []
  }
  ```

## this

- The **this** keyword is a pointer to the current object instance that the method belongs to.

- The **arrow operator** will automatically dereference a pointer (which is allocated on the heap).

  ```cpp
  class Entity {
  public:
      int x, y;
      Entity(int x, int y) {
          this->x = x;
          this->y = y;
      }
  };
  ```



# Copying (Shallow/Deep)

- Creating a **shallow copy** of an object (*string* & *second*) will mean they point to the same address in memory. When the program finishes running, it will try to call the destructor *twice* and will cause a crash (trying to free memory that is already free). 

  - If we try to alter the *second* string below, it will also alter the first string since they both point to the same value ("Tested").

- A **deep copy** means we copy the entire object, not just the address in memory. Doing this we can copy the class and change the member values without altering the other.

  - We do this by calling a **copy constructor**, which is called when assigning a variable of the same type to a copied class object.
  - If you set the copy constructor *= delete* then it disables copying and the *second* string would not compile.

- Note: if we were to pass one of the string objects to a function, we need to pass by reference (*const String& string*) otherwise they will be copied twice (below we will have 4 copies instead of 2).

  ```CPP
  class String {
  private:
      char* m_buffer;
      unsigned int m_Size;
  public:
      String(const char* string) {
          m_Size = strlen(string);
          m_Buffer = new char[m_Size + 1]; // +1 to allow room for null terminator \0
          memcpy(m_Buffer, string, m_Size);
          m_Buffer[m_Size] = 0; // set null terminator manually
      }
      
      String(const String& other) : m_Size(other.m_Size) { // copy constructor (deep copy)
          m_Buffer = new char[m_size + 1];
          memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
      } 
      
      ~String() {
          delete[] m_Buffer;
      }
      
      char& operator[](unsigned int index) { return m_Buffer[index]; } // allow changes to string 
      friend std::ostream& operator<<(std::ostream& stream, const String& string); // allow access to private members
  };
  
  std::ostream& operator<<(std::ostream& stream, const String& string) { // overload the << operator
      stream << string.m_Buffer; // since friend, can access private members outside of class
      return stream;
  }
  
  int main() {
      String string = "Tested";
      String second = string;
      
      second[2] = "a";
      
      std::cout << string << std::endl;
  }
  ```

  

# Functions

## Multiple Return Values

- If we need to return multiples values of the same type, we can return an array. But if they are different data types, we have a few options:

  - One option is **passing parameters by reference** and actually changing the value within the memory address (parameter variables defined in main code).
  - Another option is to create a **tuple** and return that from our function.
    - Note: if below instead of using a *tuple* we used a **pair**, it would be set up the same but instead we would get the values by using *tmp.first* or *tmp.second* 

  ```cpp
  #include <tuple>
  #include <utility> // used to make the tuple
  
  static std::tuple<std::string, std::string> TestFunction(const std::string& test) { // tuple function (specify data types here)
      // ... code ...
      return std::make_pair(returnval1, returnval2); // make_pair comes from utility (specify return vars) 
  }
  
  int main() {
      // ... code ...
      auto sources = TestFunction(...); // would pass string param here
      std::string element1 = std::get<0>(sources); // get first element from tuple
  }
  ```

  - Another option is to create a **struct** with the desired values and return that from the function.
    - Note: the data type of the function is the struct name, and the return names come from the struct (not the function).

  ```cpp
  struct returnMV {
      std::string value1;
      std::string value2;
  };
  
  static returnMV TestFunction(const std::string& test) {
      /// ... code ...
      return { returnval1, returnval2 };
  }
  
  int main() {
      // ... code ...
      auto sources = TestFunction(...); // would pass string param here
      std::string element1 = sources.value1; // get first element from tuple (name comes from struct, not function)
  }
  ```

### Structured Bindings (C++17)

- This allows us handle **multiple return values** much easier.

  ```cpp
  #include <tuple> 
  
  std::tuple<std::string, int> CreateTest() {
      return { "Test", 24 };
  }
  
  int main() {
      auto[name, age] = CreateTest(); // create & assign variables in one line
  }
  ```

  

## Templates

- A **template** allows us to generalize code to be used with different parameters (such as different data types).

- Below, *Print* only gets created when we call the function, and the type is specified as the data type passed to the function.

  - The template type *T* can be used throughout the function (not just as a parameter).
  - We don't technically need to specify the data type if it can be determined be the passed parameter.

  ```cpp
  template<typename T>
  void Print(T value) {
      std::cout << value << std::endl;
  }
  
  int main() {
      Print<int>(5); // T is specified as int - would also work as "Print(5);"
      Print("Hello"); // T is specified as string
  }
  ```

- Templates can also be used for **classes**. 

  - Say we want to allocate an array on the stack but don't know the size initially (this is needed when stack allocating an array). We can use a template to keep the class from compiling until it is called, at which time we know the size of our class.

  ```cpp
  template<typename T, int N> // multiple template arguments
  class Array {
  private:
      T m_Array[N]; // array of type T of size N (specified at compile time)
  public:
      int GetSize() const { return N; }
  };
  
  int main() {
      Array<std::string, 5> array;
      std::cout << array.GetSize() << std::endl;
  }
  ```


## Macros

- We can use the C++ preprocessor to create **macros** for certain operations (automate repeated code). Think of this as a "find & replace" that can also take parameters.

- We can also comment out blocks of code using #if 0 ... #endif

  ```cpp
  #define print(x) std::cout << x << std::endl
  
  #if 0
  
  // all code within this block will be disabled 
  
  #endif
  
  int main() {
      print("Test");
  }
  ```

## Function Pointers

- A **function pointer** is a way to assign a function to a variable (and pass parameters to it).

  - A function pointer gets the memory address where the compiled function is stored
  - Below the *HelloWorld* data type is a *void(\*function)()* 

  ```cpp
  void PrintValue(int value) {
      std::cout << "Value: " << value << std::endl;
  }
  
  void ForEach(cost std::vector<int>& values, void(*func)(int)) {
      for (int value : values)
          func(value);
  }
  
  int main () {
      auto function = PrintValue; // get function pointer - same as void(*function)() = HelloWorld;
      function(5); // call the stored function - Value: 5
      
      typedef void(*PrintValueFunction)(int); // define type manually
      PrintValueFunction function = PrintValue; // get function pointer
      function(8); // call the stored function - Value: 8
      
      std::vector<int> values = {1, 5, 4, 2, 3};
      ForEach(values, PrintValue);
  }
  ```

## Lambdas

- A **lambda** is a way to create a function without having to define it globally (think of this a temporary throw-away function).

  - Refer [here](https://en.cppreference.com/w/cpp/language/lambda) for cpp reference on *lambda captures* (what we can pass into the lambda functions).
  - The [ ] in the lambda function determines what is captured (i.e. = captures all variables by value).

  ```cpp
  #include <algorithm>
  #include <vector>
  #include <functional>
  
  int main () {
      std::vector<int> values = {1, 5, 4, 2, 3};
      auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
      std::cout << *it << std::endl; // 5
  }
  ```



# Namespaces

- The purpose of a **namespace** is to avoid naming conflicts.

  - We use the **scope operator** :: to use a function within a namespace. We can also write **using namespace ____** to avoid using scope operator.

  ```cpp
  namespace tmp {
      void print(const char* text) { // reverse string and print
          std::string temp = text;
          std::reverse(temp.begin(), temp.end());
          std::cout << temp << std::endl;
      }
  }
  
  int main() {
      tmp::print("Test"); //
  }
  ```



# Speed Optimizing

## Threads

- **Threads** are a way for us to do multiple tasks in parallel (run chunks of code at the same time).

  - For the below example, we print "Working..." to the console until we press enter.
  - `.join()` means that we wait for the previous thread (in this case *worker*) to finish executing before continuing with the main thread. This means no more code will be executed until the *worker* thread has finished.

  ```cpp
  #include <thread>
  
  static bool s_Finished = false;
  
  void DoWork() {
      using namespace std::literals::chrono_literals; // needed for sleep below
      std::cout << "Started thread id=" << std::this_thread_get_id() << std::endl; // print current thread id
      while(!s_Finished) {
          std:: cout << "Working...\n"; // '\n' is the same as 'std::endl'
          std::this_thread::sleep_for(1s); // pause for 1 second before running while loop again
      }
  }
  
  int main() {
      std::thread worker(DoWork);
      std::cin.get();
      s_Finished = true;
      
      worker.join(); // wait
      std::cout << "Started thread id=" << std::this_thread_get_id() << std::endl; // different id that function thread
  }
  ```

## Timing (Chrono)

- We can use the **chrono** library to time our code and evaluate the performance/speed of it.

  ```cpp
  #include <chrono>
  
  struct Timer {
      std::chrono::time_point<std::chrono::steady_clock> start, end;
      std::chrono::duration<float> duration;
      
      Timer() { // constructor
          start = std::chrono::high_resolution_clock::now();
      }
      
      ~Timer() { // destructor
          end = std::chrono::high_resolution_clock::now();
          duration = end - start;
          float ms = duration.count() * 1000.0f; // convert sec to ms 
          std::cout << "Timer took " << ms << "ms." << std::endl;
      }
  };
  
  void Function() {
      Timer timer; // create the timer
      for(int i = 0; i < 100; i++)
          std::cout << "Hello\n"; // '\n' is faster than 'std::endl'
  }
  
  int main() {
      Function();
  }
  ```

## Benchmarking

- **Benchmarking** is a way which we can evaluate the performance (mainly speed) of our code execution.

  ```cpp
  #include <chrono>
  
  class Timer {
  public:
      Timer() { // constructor
          m_StartTimepoint = std::chrono::high_resolution_clock::now();
      }
      ~Timer() { // destructor
          Stop();
      }
      void Stop() {
          auto endTimepoint = std::chrono::high_resolution_clock::now();
          auto start = std::chrono::time_point_cast<std::chrono:microseconds>(m_StartTimepoint).time_since_epoch().count();
          auto end = std::chrono::time_point_cast<std::chrono:microseconds>(endTimepoint).time_since_epoch().count();
          auto duration = end - start;
          double ms = duration * 0.001; // convert sec to ms
          std::cout << duration << "us (" << ms << "ms)\n";
      }
      
  private:
      std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
  };
  
  int main() {
      int value = 0;
      {
          Timer timer; // create within the scope
          for (int i = 0; i < 1000000; i++)
              value += 2;
      } // timer destructor will be called here
  }
  ```

  

# Casting

- **Casting** is a way for us to convert between data types.

  - C-style casting is by putting *(datatype)* before the variable you want to cast.
  - In C++, we can use **static casting** to do the same as C-style (but adds in compile-time error checking).

  ```cpp
  int main() {
      double value = 5.25;
      double a = (int)value + 5.3; // C-style: 5 + 5.3 = 10.3
      double s = static_cast<int>(value) + 5.3; // C++ style: 5 + 5.3 = 10.3
  }
  ```

## Dynamic Casting

- **Dynamic casting** is used when we have inheritance (convert from base to subclass, or subclass to base).

  - Note: dynamic casting only works with Polymorphic class types (virtual function table).

  ```cpp
  class Entity {
  public:
  	virtual void Finction () {}
  };
  class Player : public Entity { };
  class Enemy : public Entity { };
  
  int main() {
      Player* player = new Player(); // has type Entity and Player
      Entity* actuallyPlayer = player; // convert Player to Entity
      Entity* actuallyEnemy = new Enemy(); // has type Entity and Enemy
      Player* p1 = dynamic_cast<Player*>(actuallyEnemy); // returns null (can't cast between subclass)
      Player* p2 = dynamic_cast<Player*>(actuallyPlayer); // successfully casts to Player
  }
  ```

## Type Punning

- This is a way for use to get around the *type* system in C++. The main way we do this is by getting the type as a *pointer*, and then *casting* it to a different pointer type.

  ```cpp
  struct Entity {
      int x, y;
  };
  
  int main() {
      Entity e = { 5, 8 };
      int* position = (int*)&e; // position points at the beginning of an array
      std::cout << position[0] << ", " << position[1] << std::endl;
  }
  ```



# Unions

- A **union** can only have a single member (occupy one block of memory) at a time.

  - This is mainly used when we want to have multiple ways to assign the same values.

  ```cpp
  struct Vector2 {
      float x, y;
  };
  
  struct Vector4 {
      union { // union only contains one thing - a struct (of 4 floats), 16 bytes
          struct { // anonymous struct
              float x, y, z, w;
          };
          struct { // anonymous struct of 2 Vector2 structs
              Vector2 a, b;
          }
      };
  };
  
  void PrintVector2(const Vector2& vector) {
      std::cout << vector.x << ", " << vector.y << std::endl;
  }
  
  int main() {
      Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };
      PrintVector2(vector.a); // prints 1, 2
      PrintVector2(vector.b); // prints 3, 4
      vector.z = 500.f;
      PrintVector2(vector.a); // prints 1, 2
      PrintVector2(vector.b); // prints 500, 4
  }
  ```




# Singletons

- A **singleton** is a single instance of a class/struct, mainly used to organize global variables and static functions into one organize section (basically a *namespace*).

  - Mainly used when we have functions that we want to apply to a global set of data that we want to reuse.

  ```cpp
  class Random {
  public:
      Random(const Random&) = delete; // set copy constructor to delete if new instance is attemmpted to be made
      static Random& Get() { // main code of singleton
          static Random instance; // instantiate single instance
          return instance; // return instance
      }
      static float Float() { return Get().IFloat(); } // public function to "Get" value from function
      
  private:
      float IFloat() { return m_RandomGenerator; } // internal function that returns class member
      Random() {} // put constructor as private so it can't be instantiated outside of the class
      float m_RandomGenerator = 0.5f; // used as our "random" number
  };
  
  
  int main() {
  	float number = Random::Float(); // could be Random::Get().Float(); if no internal and static function
  }
  ```

  

# Optional Data (C++17)

- The **std::optional** library gives us an easier way of dealing with determining if data is present or not.

  - This could be use for something such as checking to ensure that a text file was read in and isn't empty (reduce number of lines in code).
  - We can also set a default value using the *.value_or()* function, which checks for value and if none found, assigns the parameter.

  ```cpp
  #include <fstream>
  #include <optional>
  
  std::optional<std::string> ReadFileAsString(const std::string& filepath) {
      std::ifstream stream(filepath);
      if (stream) {
          std::string result;
          // read file ...
          stream close;
          return result; // return std::string that is read from text file
      }
      return { }; // if stream obj doesn't exist, return our std::optional
  }
  
  int main() {
      std::optional<std::string> data = ReadFileAsString("data.txt");
      std::string value = data.value_or("Not present"); // check for value, if none assign "Not present"
      std::cout << value;
      
      if(data.has_value()) // can also write "if (data)"
          std::cout << "File read successfully!\n";
      else
          std::cout << "File read successfully!\n";
  }
  ```

  

# Multiple Types, Single Var (C++17)

- The **std::variant** library allows us to not have to worry about the data type we deal with, but have a single variable and decide later.

  - This could be used for command line arguments where we don't know what the user will input.
  - Note that we have to use *std::get* in order to retrieve the value from the variable.
  - Variant basically creates a struct for you and allocates enough memory to store either type (adds together all data types sizes).

  ```cpp
  #include <variant>
  
  int main() {
      std::variant<std::string, int> data;
      std::cout << sizeof(data) << std::endl; // 32 (4 byte int + 28 byte string)
      data = "Test";
      std::cout << std::get<std::string>(data) << "\n"; // get value from data variable
      if (auto value = std::get_if<std::string(&data)) // get_if returns pointer (nullptr if not string, ptr if is string)
          std::string& v = *value;
      data = 2;
  }
  ```



# lvalues & rvalues

- **lvalues** are variable with a location in memory of the *left side* of the assignment operator.

  - Passing parameters *by reference* is considered to be passing lvalues into functions.

- **rvalues** are the actual value that is being assign on the *right side* of the assignment operator (no storage/location until assigned to lvalue).

  - We can pass by *rvalue reference* in order to take temporary variables into functions.

- Note: below we could write two functions both named PrintName and use function overwriting for the code to choose the right one.

  ```cpp
  void PrintNameL(std::string& name) { // pass by reference - requires lvalue
      std::cout << name << std::endl;
  }
  
  void PrintNameR(std::string&& name) { // pass by rvalue reference - &&
      std::cout << name << std::endl;
  }
  
  int main() {
      std::string firstName = "Derek"; // lvalue - firstName, rvalue - "Derek"
      std::string lastName = "Helms"; // lvalue - lastName, rvalue - "Helms"
      std::string fullName = firstName + lastName; // lvalue - fullName, rvalue - "Derek Helms"
      
      PrintNameL(fullName); // works since passing by reference & fullName is lvalue
      PrintNameL(firstName + lastName); // wont work since we are trying to pass rvalue into lvalue function
      
      PrintNameR(firstName + lastName); // works since function expects rvalue reference - temporary variable
      PrintNameR(fullName); // wont work since this is an lvalue
  }
  ```

## Move Semantics

- **Move semantics** allows us to move objects around (ex: avoid copying when passing/returning an object from a function).

  ```cpp
  class String {
  public:
      String() = default;
      String(const char* string) {
          m_Size = strlen(string);
          m_Data = new char[m_Size];
          memcpy(m_Data, string, m_Size);
      }
      String(String&& other) noexcept { // rvalue move constructor, no copying
          m_Size = other.m_Size; // shallow copy size
          m_Data = other.m_Data; // shallow copy data
          other.m_Size = 0; // set old string to empty
          other.m_Data = nullptr; // remove reference
      }
      ~String() { delete[] m_Data; }
  private:
      char* m_Data;
      uint32_t m_Size;
  };
  
  class Entity {
  public:
      Entity(const String& name) : m_Name(name) { } // creates copy
      Entity(String&& name) : m_Name((String&& name) { } // takes an rvalue - temporary & no copy
  private:
      String m_Name;
  };
  
  
  int main() {
      Entity entity("Derek"); // no copies, uses move constructor
  }
  ```

## Move Assignment

- Instead of moving an object when creating, we can also use **move assignments** to move objects after being created.

  - We can do this by casting the object we want to move into a *temporary* variable using **std::move**.

- We can **assign** an existing object into another object by using an *assign* operator overload.

  ```cpp
  class String {
  public:
      String() = default;
      String(const char* string) {
          m_Size = strlen(string);
          m_Data = new char[m_Size];
          memcpy(m_Data, string, m_Size);
      }
      String(String&& other) noexcept { // rvalue move constructor, no copying
          m_Size = other.m_Size; // shallow copy size
          m_Data = other.m_Data; // shallow copy data
          other.m_Size = 0; // set old string to empty
          other.m_Data = nullptr; // remove reference
      }
      String& operator=(String&& other) noexpect { // assign operator to move into exisiting variable
          if (this != &other) { // if object are equal (move into itself), no reassignment needed
              delete[] m_Data; // delete current object to avoid memory leak
              m_Size = other.m_Size; // shallow copy size
              m_Data = other.m_Data; // shallow copy data
              other.m_Size = 0; // set old string to empty
              other.m_Data = nullptr; // remove reference
          }
          return *this; // return pointer to object
      }
      ~String() { delete[] m_Data; } // destructor
  private:
      char* m_Data;
      uint32_t m_Size;
  };
  
  
  int main() {
      String apple = "Apple";
      String dest; // empty object
      dest = std::move(apple); // move contents of apple into dest (apple is now empty)
  }
  ```




# Iterators

- **Iterators** are used to iterate over a collection of elements.

- The **std::vector** has an *iterator* method which will go from beginning to end of the vector.

  - Note that it also has a *reverse_iterator* which goes from end to beginning for the vector.

  ```cpp
  int main() {
      std::vector<int> values = { 1, 2, 3, 4, 5 };
      
      for (int value : values)
          std::cout << value << std::endl;
      
      for (int i = 0; i < values.size(); i++)
          std::cout << values[i] << std::endl;
      
      for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
          std::cout << *it << std::endl; // need to derefernce the iterator (get object it points to)
  }
  ```

## Unordered Map

- An **unordered map** is basically a hash map that doesn't store it's variables in any order.

  - You need to know the key to get the value, unless you *iterate* through them.

  ```cpp
  #include <unordered_map>
  
  int main() {
      using ScoreMap = std::unordered_map<std::string, int>; // define data type to avoid long names
      ScoreMap map;
      map["Derek"] = 5;
      map["Helms"] = 2;
      
      for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++) { // using iterators
          auto& key = it->first;
          auto& value = it->second;
          std::cout << key << " = " << value << std::endl;
      }
      
      for (auto kv :: map) { // retrieve an std::pair of (key, value)
          auto& key = kv.first;
          auto& value = kv.second;
          std::cout << key << " = " << value << std::endl;
      }
      
      for (auto [key, value] :: map) // use structured bindings (only for C++17 or newer)
          std::cout << key << " = " << value << std::endl;
  }
  ```

  

// ========================================================================
// VariadicTemplate_01_Introduction.cpp // Variadic Templates: Introduction
// ========================================================================

module modern_cpp:variadic_templates;

namespace VariadicTemplatesSeminar {

    // ========================================================================
// Test-Klasse Unknown
// Nur die Konstruktoren sind interessant
// ========================================================================

    class Unknown {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        Unknown(const Unknown& other)
            : m_var1{ other.m_var1 }, m_var2{ other.m_var2}, m_var3{ other.m_var3 } {
            std::cout << "copy c'tor()" << std::endl;
        }

        Unknown(Unknown&& other) noexcept
            : m_var1{ other.m_var1 }, m_var2{ other.m_var2 }, m_var3{ other.m_var3 } {
            
            other.m_var1 = 0;
            other.m_var2 = 0;
            other.m_var3 = 0;

            std::cout << "move c'tor()" << std::endl;
        }

        Unknown() : m_var1{ -1 }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) : m_var1{ n }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(double d1, double d2, long l) {
            std::cout << "c'tor(double, double, long)" << std::endl;
        }

        Unknown(int n, int m) : m_var1{ n }, m_var2{ m }, m_var3{ -1 } {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) : m_var1{ n }, m_var2{ m }, m_var3{ k } {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        friend std::ostream& operator<< (std::ostream&, const Unknown&);
    };

    std::ostream& operator<< (std::ostream& os, const Unknown& obj) {
        os
            << "var1: " << obj.m_var1
            << ", var2: " << obj.m_var2
            << ", var3: " << obj.m_var3 << std::endl;

        return os;
    }
    
    // C++ 11: zwei Funktionen
    // C++ 17: einer Funktion
    // Sammelname: Parameter Pack
    // C++20: Generische Funktionen
    // Pack: for - each

    // C++ 11
    //template <typename T>
    //void printer(T n) {
    //    std::cout << n << std::endl;
    //}

    //template <typename T, typename ... TRest>    // einpacken
    //void printer(T n, TRest ... args) {          // einpacken
    //    std::cout << n << std::endl;
    //    printer(args ...);
    //}

    //void printer(auto n) {
    //    std::cout << n << std::endl;
    //}

    //void printer(auto n, auto ... args) {
    //    std::cout << n << std::endl;
    //    printer(args ...);
    //}

    // C++ 17
    //template <typename T, typename ... TRest> 
    //void printer(T n, TRest ... args) { 

    //    std::cout << n << std::endl;

    //    if constexpr (sizeof... (args) > 0)
    //    {
    //        printer(args ...);
    //    }
    //}

    // C++ 20
    void printer(auto n, auto ... args) { 

        std::cout << n << std::endl;

        if constexpr (sizeof... (args) > 0)
        {
            printer(args ...);
        }
    }

    void testSeminar_intro() {

        printer(1, 2, 3, 4, 5);
    }

    // ===================================================

    // 1. Motivation // Why

    // a) Geht, aber KOPIEN
    template <typename T, typename ... TArgs>
    auto my_make_unique_01 (TArgs ... args) {

        std::unique_ptr<T> up{ new T { args ... } };
        return up;
    }

    // b) Geht, und es werden Adressen / Referenzen �bergeben
    template <typename T, typename ... TArgs>
    auto my_make_unique(TArgs&& ... args) {

        std::unique_ptr<T> up{ new T { std::forward<TArgs>(args) ...  }};
        return up;
    }

    void testSeminar() {

        int x = 123;

        std::unique_ptr<Unknown> up {
            my_make_unique<Unknown>(1, 2, x)
        };
    }

    // ===================================================

    // 2. Motivation // Why // emplace

    void testSeminar_emplace() {

        std::vector<Unknown> vec;

        vec.push_back(Unknown{ 4, 5, 6 });   // a) user-defined c'tor // b) move-c'tor

        vec.emplace_back(1, 2, 3);
    }

    // ===================================================

    // 3. Frage // for_each

    // C++ 11:  Parameter Pack:  ... args // args ...


    // C++ 20
    void my_for_each(auto ... args)
    {
        auto list = { args ... };

        //for (auto n : list) {
        //    std::cout << n << '\n';
        //}

        for (auto n : { args ...  }) {
            std::cout << n << '\n';
        }
    }


    // C++ 11
    template <typename TFirst, typename ... TArgs>
    void my_for_each_11(TFirst first, TArgs ... args)
    {
        // auto list = { args ... };

        std::initializer_list<TFirst> list = { first, args ... };

        for (auto n : list) {
            std::cout << n << '\n';
        }
    }

    void testSeminar_forEach() {

        my_for_each(1, 2, 3, 4, 5, 6);
    }

}














namespace VariadicTemplatesIntro_01 {

    // ====================================================================
    // 1. Beispiel f�r ein variadisches Template:
    // Eine print-Funktion mit beliebig vielen Argumenten
    // ====================================================================

    // Non-recursive template part (regular template)
    template <typename T>
    void print(T value)
    {
        std::cout << value << " ";
    }

    // Recursive template part
    template <typename T, typename ... TRest>
    void print(T n, TRest ... rest)
    {
        print<T>(n);
        print<TRest...>(rest ...);
    }

    static void test_printer_01()
    {
        print<int, int, int, int, int>(1, 2, 3, 4, 5);
    }
}

namespace VariadicTemplates_TestClassUnknown {

    // ========================================================================
    // Test-Klasse Unknown
    // Nur die Konstruktoren sind interessant
    // ========================================================================

    class Unknown {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        Unknown() : m_var1{ -1 }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) : m_var1{ n }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(int n, int m) : m_var1{ n }, m_var2{ m }, m_var3{ -1 } {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) : m_var1{ n }, m_var2{ m }, m_var3{ k } {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        friend std::ostream& operator<< (std::ostream&, const Unknown&);
    };

    std::ostream& operator<< (std::ostream& os, const Unknown& obj) {
        os 
            << "var1: " << obj.m_var1
            << ", var2: " << obj.m_var2
            << ", var3: " << obj.m_var3 << std::endl;

        return os;
    }
}

namespace VariadicTemplatesIntro_02 {

    // =============================================================
    // 2. Beispiel f�r ein variadisches Template:
    // Anwendungsfall: Standardfunktion std::unique_ptr<>
    // =============================================================

    using namespace VariadicTemplates_TestClassUnknown;

    // einfache Variante
    template<typename T, typename... TArgs>
    std::unique_ptr<T> my_make_unique(TArgs... args)
    {
        return std::unique_ptr<T>{ new T{ args... } };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename... TArgs>
    std::unique_ptr<T> my_make_unique_ex(TArgs&&... args)
    {
        return std::unique_ptr<T>{ new T{ std::forward<TArgs>(args)... } };
    }

    static void test_my_make_unique()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique<Unknown>(n, m);
    }

    static void test_my_make_unique_ex()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique_ex<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique_ex<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique_ex<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique_ex<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique_ex<Unknown>(n, m);
    }
}

namespace VariadicTemplatesIntro_03 {

    // =============================================================
    // 3. Beispiel f�r ein variadisches Template:
    // Anwendungsfall: Zugriff auf die einzelnen Elemente eines Parameter Packs
    // =============================================================

    template <typename... TArgs>
    void func(TArgs... args) {

        // unpack all function arguments with the help of a std::initializer_list object
        auto unpackedArgs = { args ... };

        for (auto param : unpackedArgs) {
            std::cout << "Passed Argument: " << param << std::endl;
        }
    }

    static void test_accessing_parameterpack()
    {
        func(10, 11, 12, 13, 14, 15);
    }
}

namespace VariadicTemplatesIntro_04 {

    // =================================================================================
    // 4. Beispiel f�r ein variadisches Template:
    // 
    // Anwendungsfall: "Generische Funktion 'make_an_object'"
    //                 Umsetzung Parameter Pack auf einen passenden Konstruktor
    // 
    // Siehe Analogien zu Factory-Pattern
    // =================================================================================

    using namespace VariadicTemplates_TestClassUnknown;

    // einfache Variante
    template<typename T, typename... TArgs>
    T make_an_object(const TArgs&... args)
    {
        return T{ args... };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename... TArgs>
    T make_an_object_ex(TArgs&&... args)
    {
        return T{ std::forward<TArgs>(args)... };
    }

    static void test_make_an_object()
    {
        Unknown u1 = make_an_object<Unknown>();
        Unknown u2 = make_an_object<Unknown>(1);
        Unknown u3 = make_an_object<Unknown>(10, 11);
        Unknown u4 = make_an_object<Unknown>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        Unknown u5 = make_an_object<Unknown, int, int&, const int&>(100, n, m);
        Unknown u6 = make_an_object<Unknown>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;

        // doesn't compile: too much parameters
        // Unknown u7 = make_an_object<Unknown>(1000, 1001, 1002, 1003);
        // std::cout << u7 << std::endl;
    }

    static void test_make_an_object_ex()
    {
        Unknown u1 = make_an_object_ex<Unknown>();
        Unknown u2 = make_an_object_ex<Unknown>(1);
        Unknown u3 = make_an_object_ex<Unknown>(10, 11);
        Unknown u4 = make_an_object_ex<Unknown>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        Unknown u5 = make_an_object_ex<Unknown, int, int&, const int&>(100, n, m);
        Unknown u6 = make_an_object_ex<Unknown>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;
    }
}

namespace VariadicTemplatesIntro_05 {

    // ========================================================================
    // 5.) Drittes Beispiel:
    // Ein variadisches Template in zwei Realisierungsvarianten.
    // 
    // Ende der Rekursion:
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Non-Template Funktion
    // 
    // Man beachte: Wenn sich zwei Template Funktionen nur um das Parameter Pack
    // unterscheiden, wird - wenn m�glich - die Template Funktionen ohne Parameter Pack bevorzugt:
    // ========================================================================

    // Ende der Rekursion: Eine non-Template Funktion
    static void print()
    {
    }

    template<typename T, typename... Types>
    void print(T firstArg, Types... args)
    {
        std::cout << firstArg << std::endl; // print first argument
        print(args...); // call print() for remaining arguments
    }

    // Oder:
    // Ende der Rekursion: Eine Template Funktion

    template<typename T>
    void printEx(T arg)
    {
        std::cout << arg << std::endl; // print passed argument
    }

    template<typename T, typename... Types>
    void printEx(T firstArg, Types... args)
    {
        printEx(firstArg); // call print() for first argument
        printEx(args...);  // call print() for remaining arguments
    }

    static void test_printer_02()
    {
        print(123.456, "Hello", 789);
        print<double, const char*, int>(123.456, "Hello", 789);

        printEx(123.456, "Hello", 789);
        printEx<double, const char*, int>(123.456, "Hello", 789);
    }
}


void main_variadic_templates_introduction()
{
    using namespace VariadicTemplatesSeminar;
    testSeminar();
    return;

    using namespace VariadicTemplatesIntro_01;
    test_printer_01();

    using namespace VariadicTemplatesIntro_02;
    test_my_make_unique();
    test_my_make_unique_ex();

    using namespace VariadicTemplatesIntro_03;
    test_accessing_parameterpack();

    using namespace VariadicTemplatesIntro_04;
    test_make_an_object();
    test_make_an_object_ex();

    using namespace VariadicTemplatesIntro_05;
    test_printer_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================

// =====================================================================================
// Folding.cpp // Variadic Templates // Folding
// =====================================================================================

module modern_cpp:folding;


template<typename ... TArgs>

static void logInternal(std::ostream& os, TArgs&& ...args)
{
    std::stringstream ss;
 //   ss << getPrefix();
    ss << '\t';

    // viele Male <<: Feht, weil ss liegt am Stack
    (ss << ... << std::forward<TArgs>(args)) << std::endl;

    os << ss.str();   // einmal << ist thread-safe
}


namespace Folding_Seminar {

    void test()
    {
        logInternal(std::cout, "Der Wert ist:" , 123, ".");
    }

    template <typename ... TArgs>
    auto addierer(TArgs ... args) {

        auto tmp = (... + args) ;   // 3 Beteiligte: +   args ...
        return tmp;
    }

    template <typename ... TArgs>
    auto subtrahierer(TArgs ... args) {

        // auto tmp = (... - args); 
        auto tmp = (args - ...);
        return tmp;
    }

    template <typename ... TArgs>
    void printer (TArgs ... args) {

        // (((std::cout << pack1) << pack2) << ...) << packN

        (std::cout << ... << args);
    }

    template <typename TFirst, typename ... TArgs>
    void printerEx(TFirst first, TArgs ... args) {

        // (((std::cout << pack1) << pack2) << ...) << packN

        // Filding �ber einem Komma: Sequenz

        std::cout << first;

        ( ... , (  std::cout << " - " << args ) );
    }



    void testFolding() {

        //int a;
        //int b;
        //int c;

        //a = 10; b = 20;

        //if (  c = (a = 10, b = 20) ) {

        //}

        auto result = addierer(1, 2, 3, 4, 5);

        printerEx(1, 123.456, "ABC", '?', false);

        std::cout << std::endl;
    }

}









namespace Folding {

    /* folding examples: introduction
    */

    template<typename... TArgs>
    static auto anotherAdder(TArgs... args) {
        return (args + ... + 0);  // binary right fold (init == 0)
    }

    static void test_01() {
        int sum = anotherAdder(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;
    }

    template<typename... TArgs>
    static void printer(TArgs... args) {
        // binary left fold (init == ostream)
        (std::cout << ... << args) << std::endl;
    }

    // demonstrating fold expressions
    static void test_02() {
        printer(1, 2, 3, "ABC", "DEF", "GHI");
    }

    // =================================================================================
    /* demonstrating all four versions of folding expressions
    */

    template<typename... TArgs>
    static auto anotherSubtracterBRF(TArgs... args) {
        return (args - ... - 0);  // binary right fold (init == 0)
    }

    static void test_03a() {
        // binary right fold: 1 - (2 - (3 - (4 - ( 5 - 0)))) = 3
        int result = anotherSubtracterBRF(1, 2, 3, 4, 5);
        std::cout << "BRF: 1 - (2 - (3 - (4 - ( 5 - 0)))): " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    template<typename... TArgs>
    static auto anotherSubtracterBLF(TArgs... args) {
        return (0 - ... - args);  // binary left fold (init == 0)
    }

    static void test_03b() {
        // binary left fold: ((((0 - 1) - 2) - 3) - 4) - 5 =  -15
        int result = anotherSubtracterBLF(1, 2, 3, 4, 5);
        std::cout << "BLF: ((((0 - 1) - 2) - 3) - 4) - 5: " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    template<typename... TArgs>
    static auto anotherSubtracterURF(TArgs... args) {
        return (args - ...);  // unary right fold
    }

    static void test_03c() {
        // unary right fold: 1 - (2 - (3 - (4 - 5))) = 3
        int result = anotherSubtracterURF(1, 2, 3, 4, 5);
        std::cout << "URF: 1 - (2 - (3 - (4 - 5))): " << result << std::endl;
    }

    // ----------------------------------------------------------------------

    template<typename... TArgs>
    static auto anotherSubtracterULF(TArgs... args) {
        return (... - args);  // unary left fold
    }

    static void test_03d() {
        // unary left fold: ((((1 - 2) - 3) - 4) - 5 = -13
        int result = anotherSubtracterULF(1, 2, 3, 4, 5);
        std::cout << "URF: ((((1 - 2) - 3) - 4) - 5: " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    // Folding over a comma: ',' operator
    // (left or right folding is the same in this case)

    template <typename... TArgs>
    static void printerWithSeperatorRight(TArgs... args) {
        std::string sep = " ";
        ((std::cout << args << sep), ...) << std::endl;
    }

    template <typename... TArgs>
    static void printerWithSeperatorLeft(TArgs... args) {
        std::string sep = " ";
        (... , (std::cout << args << sep)) << std::endl;
    }

    // demonstrating fold expressions
    static void test_04() {
        printerWithSeperatorRight(1, 2, 3, "ABC", "DEF", "GHI");
        printerWithSeperatorLeft (1, 2, 3, "ABC", "DEF", "GHI");
    }

    // -----------------------------------------------------------------------

    // Folding over a comma - pack arguments can be handled by a separate function

    template <typename T>
    static std::ostream& handleArg(T arg) {
        std::cout << arg << "-";
        return std::cout;
    }

    template <typename... TArgs>
    static void printerWithSeperator(TArgs... args) {
        (handleArg(args), ...) << std::endl;
    }

    // demonstrating fold expressions
    static void test_05() {
        printerWithSeperator(1, 2, 3, "ABC", "DEF", "GHI");
    }
}


void main_folding()
{
    using namespace Folding_Seminar;
    testFolding();
    return;

    using namespace Folding;
    test_01();
    test_02();
    test_03a();
    test_03b();
    test_03c();
    test_03d();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================

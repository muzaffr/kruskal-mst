#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include <string>

/**
 * Custom input class designed for better performance than conventional methods,
 * such as std::cin or scanf.
 */
class Input
{
private:
    static const int _BUF_SIZE = 4096;      ///< Input buffer size (for STDIN).
    inline static int _eof_found;           ///< Indicates if EOF has been encountered.

    /**
     * Gets next character from the buffer. Reads STDIN into buffer
     * if buffer is empty.
     * @return the character read.
     */
    inline static char _get_char();

    /**
     * Reads the next non-whitespace character from the input buffer.
     * @return the character read.
     */
    inline static char _read_char();

    /**
     * Reads the next (whitespace-separated) integer from the input buffer.
     * @return the integer read.
     */
    template <class T = int64_t> inline static T _read_int();

    /**
     * Chained istream operator for reading a character from the input buffer.
     * @param[in] in instance of Input class.
     * @param[out] x variable in which the char is to be read.
     * @return reference to the Input instance for chaining.
     */
    friend Input& operator >> (Input& in, char& x);

    /**
     * Chained istream operator for reading an integer from the input buffer.
     * @param[in] in instance of Input class.
     * @param[out] x int variable in which the integer is to be read.
     * @return reference to the Input instance for chaining.
     */
    friend Input& operator >> (Input& in, int& x);

    /**
     * Chained istream operator for reading an integer from the input buffer.
     * @param[in] in instance of Input class.
     * @param[out] x int64_t variable in which the integer is to be read.
     * @return reference to the Input instance for chaining.
     */
    friend Input& operator >> (Input& in, int64_t& x);

    /**
     * Chained istream operator for reading a string from the input buffer.
     * @param[in] in instance of Input class.
     * @param[out] s std::string variable in which the integer is to be read.
     * @return reference to the Input instance for chaining.
     */
    friend Input& operator >> (Input& in, std::string& s);

public:
    /**
     * bool() overloaded to indicate whether EOF has been encountered.
     */
    explicit operator bool();
};

/**
 * Custom output class designed for better performance than conventional methods,
 * such as std::cout or printf.
 */
class Output
{
    static const int _BUF_SIZE = 65536;         ///< Output buffer size (for STDOUT).
    inline static int _write_pos;               ///< Current writing position in the output buffer.
    inline static char _write_buf[_BUF_SIZE];   ///< Output buffer.

    /**
     * Writes a character to the output buffer.
     * @param[in] x Character to be written.
     */
    inline static void _write_char(int x);

    /**
     * Writes an integer to the output buffer.
     * @param[in] x Integer to be written.
     */
    template <class T>
    inline static void _write_int(T x);

    /**
     * Chained ostream operator for writing an integer to the output buffer.
     * @param[in] out   Instance of Output class.
     * @param[in] x     Integer to be written.
     * @return reference to the Output instance for chaining.
     */
    friend Output& operator << (Output& out, int x);

    /**
     * Chained ostream operator for writing an integer to the output buffer.
     * @param[in] out   Instance of Output class.
     * @param[in] x     Integer to be written.
     * @return reference to the Output instance for chaining.
     */
    friend Output& operator << (Output& out, int64_t x);

    /**
     * Chained ostream operator for writing a character to the output buffer.
     * @param[in] out   Instance of Output class.
     * @param[in] c     Character to be written.
     * @return reference to the Output instance for chaining.
     */
    friend Output& operator << (Output& out, char c);

    /**
     * Chained ostream operator for writing an std::string to the output buffer.
     * @param[in] out   Instance of Output class.
     * @param[in] s     String to be written.
     * @return reference to the Output instance for chaining.
     */
    friend Output& operator << (Output& out, std::string s);

    /**
     * Chained ostream operator for writing an C-style string to the output buffer.
     * @param[in] out   Instance of Output class.
     * @param[in] s     String to be written.
     * @return reference to the Output instance for chaining.
     */
    friend Output& operator << (Output& out, const char* s);

public:
    /**
     * Destructor. Flushes the output buffer.
     */
    ~Output();
};

#endif

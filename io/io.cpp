#include "io.hpp"

char Input::_get_char()
{
    static char buf[_BUF_SIZE]; ///< Input buffer.
    static int len, pos;
    if (pos == len)
        pos = 0, len = (int) fread(buf, 1, _BUF_SIZE, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}

char Input::_read_char()
{
    char c;
    do
        c = _get_char();
    while (c <= 32 and c >= 0);
    if (c == -1)
        _eof_found = 1;
    return c;
}

Input& operator >> (Input& in, char& x)
{
    x = (char) Input::_read_char();
    return in;
}

template <class T = int64_t>
T Input::_read_int()
{
    int s = 1, c = _read_char();
    T x = 0;
    if (c == '-')
        s = 0, c = _get_char();
    while ('0' <= c and c <= '9')
        x = x * 10 + c - '0', c = _get_char();
    return s ? x : -x;
}

Input& operator >> (Input& in, int& x)
{
    x = (int) Input::_read_int();
    return in;
}

Input& operator >> (Input& in, int64_t& x)
{
    x = Input::_read_int();
    return in;
}

Input& operator >> (Input& in, std::string& s)
{
    s.clear();
    char c = Input::_read_char();
    while (c > 32)
        s += c, c = Input::_get_char();
    return in;
}

Input::operator bool()
{
    return not _eof_found;
}


void Output::_write_char(int x)
{
    if (_write_pos == _BUF_SIZE)
        fwrite(_write_buf, 1, _BUF_SIZE, stdout), _write_pos = 0;
    _write_buf[_write_pos++] = (char) x;
}

template <class T>
void Output::_write_int(T x)
{
    if (x < 0)
        _write_char('-'), x = -x;
    char s[24];
    int n = 0;
    while (x or !n)
        s[n++] = char('0' + x % 10), x /= 10;
    while (n--)
        _write_char(s[n]);
}

Output& operator << (Output& out, int x)
{
    Output::_write_int(x);
    return out;
}

Output& operator << (Output& out, int64_t x)
{
    Output::_write_int(x);
    return out;
}

Output& operator << (Output& out, char c)
{
    Output::_write_char(c);
    return out;
}

Output& operator << (Output& out, std::string s)
{
    for (char c : s)
        Output::_write_char(c);
    return out;
}

Output& operator << (Output& out, const char* s)
{
    while (*s)
        Output::_write_char(*s++);
    return out;
}

Output::~Output()
{
    if (_write_pos)
        fwrite(_write_buf, 1, _write_pos, stdout), _write_pos = 0;
}

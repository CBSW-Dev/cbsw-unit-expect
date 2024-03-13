#pragma once

#include <sstream>
#include <type_traits>

namespace CBSW::Unit::Expect::Internal {
    template <class T> class StreamBase {
    public:
        StreamBase(const T& value):
            value(value)
        {}
    protected:
        const T& value;
    };

    template <class T, class TStream, class = void> class Stream_SFINAE_1 {
    public:
        static TStream& stream(TStream& stream, const T& value) noexcept {
            stream << value;
            return stream;
        }
    };

    template <class T, class TStream> class Stream_SFINAE_1<T, TStream, std::enable_if_t<std::is_same_v<bool, T>>> {
    public:
        static TStream& stream(TStream& stream, bool value) noexcept {
            stream << (value == true ? "true" : "false");
            return stream;
        }
    };

    template <class T, class TStream> class Stream_SFINAE_1<T, TStream, std::enable_if_t<std::is_same_v<char, T>>> {
    public:
        static TStream& stream(TStream& stream, char value) noexcept {
            stream << '\'' << value << '\'';
            return stream;
        }
    };

    template <class T, class TStream> class Stream_SFINAE_1<T, TStream, std::enable_if_t<std::is_same_v<char*, std::remove_cv_t<T>>>> {
    public:
        static TStream& stream(TStream& stream, const char* value) noexcept {
            stream << '\"' << value << '\"';
            return stream;
        }
    };

    template <class T, class TStream> class Stream_SFINAE_1<T, TStream, std::enable_if_t<std::is_array_v<T> && std::is_same_v<char, std::remove_extent_t<T>>>> {
    public:
        static TStream& stream(TStream& stream, const char* value) noexcept {
            stream << '\"' << value << '\"';
            return stream;
        }
    };

    template <class T, class TStream> class Stream_SFINAE_1<T, TStream, std::enable_if_t<std::is_same_v<std::string, T>>> {
    public:
        static TStream& stream(TStream& stream, const T& value) noexcept {
            stream << '\"' << value << '\"';
            return stream;
        }
    };

    template <class T, class TStream, class = void> class Stream: public StreamBase<T> {
    public:
        using StreamBase<T>::StreamBase;

        TStream& stream(TStream& stream) const noexcept{
            stream << "[[Unstreamable Object]]";
            return stream;
        }
    };

    template <class T, class TStream> class Stream<T, TStream, std::void_t<decltype(std::declval<TStream&>() << std::declval<T>())>>: public StreamBase<T> {
    public:
        using StreamBase<T>::StreamBase;

        TStream& stream(TStream& stream) const noexcept {
            return Stream_SFINAE_1<T, TStream>::stream(stream, this->value);
        }
    };
}

template <class T, class TStream> TStream& operator << (TStream& stream, const ::CBSW::Unit::Expect::Internal::Stream<T, TStream>& value) {
    return value.stream(stream);
}

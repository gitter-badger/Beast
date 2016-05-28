//
// Copyright (c) 2013-2016 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_HTTP_DETAIL_BASIC_PARSER_V1_HPP
#define BEAST_HTTP_DETAIL_BASIC_PARSER_V1_HPP

#include <boost/system/error_code.hpp>
#include <boost/utility/string_ref.hpp>
#include <array>
#include <cstdint>

namespace beast {
namespace http {
namespace detail {

template<class = void>
struct parser_str_t
{
    static char constexpr close[6] = "close";
    static char constexpr chunked[8] = "chunked";
    static char constexpr keep_alive[11] = "keep-alive";

    static char constexpr upgrade[8] = "upgrade";
    static char constexpr connection[11] = "connection";
    static char constexpr content_length[15] = "content-length";
    static char constexpr proxy_connection[17] = "proxy-connection";
    static char constexpr transfer_encoding[18] = "transfer-encoding";
};

template<class _>
char constexpr
parser_str_t<_>::close[6];

template<class _>
char constexpr
parser_str_t<_>::chunked[8];

template<class _>
char constexpr
parser_str_t<_>::keep_alive[11];

template<class _>
char constexpr
parser_str_t<_>::upgrade[8];

template<class _>
char constexpr
parser_str_t<_>::connection[11];

template<class _>
char constexpr
parser_str_t<_>::content_length[15];

template<class _>
char constexpr
parser_str_t<_>::proxy_connection[17];

template<class _>
char constexpr
parser_str_t<_>::transfer_encoding[18];

using parser_str = parser_str_t<>;

class parser_base
{
protected:
    enum state : std::uint8_t
    {
        s_dead = 1,

        s_req_start,
        s_req_method_start,
        s_req_method,
        s_req_space_before_url,
        s_req_url_start,
        s_req_url,
        s_req_http_start,
        s_req_http_H,
        s_req_http_HT,
        s_req_http_HTT,
        s_req_http_HTTP,
        s_req_major_start,
        s_req_major,
        s_req_minor_start,
        s_req_minor,
        s_req_line_end,

        s_res_start,
        s_res_H,
        s_res_HT,
        s_res_HTT,
        s_res_HTTP,
        s_res_major_start,
        s_res_major,
        s_res_minor_start,
        s_res_minor,
        s_res_status_code_start,
        s_res_status_code,
        s_res_status_start,
        s_res_status,
        s_res_line_almost_done,
        s_res_line_done,

        s_header_field_start,
        s_header_field,
        s_header_value_start,
        s_header_value_discard_lWs0,
        s_header_value_discard_ws0,
        s_header_value_almost_done0,
        s_header_value_text_start,
        s_header_value_discard_lWs,
        s_header_value_discard_ws,
        s_header_value_text,
        s_header_value_almost_done,

        s_headers_almost_done,
        s_headers_done,

        s_chunk_size_start,
        s_chunk_size,
        s_chunk_parameters,
        s_chunk_size_almost_done,

        // states below do not count towards
        // the limit on the size of the message

        s_body_identity0,
        s_body_identity,
        s_body_identity_eof0,
        s_body_identity_eof,

        s_chunk_data_start,
        s_chunk_data,
        s_chunk_data_almost_done,
        s_chunk_data_done,

        s_complete,
        s_restart,
        s_closed_complete
    };
};

} // detail
} // http
} // beast

#endif

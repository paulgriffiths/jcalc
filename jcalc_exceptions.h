/*
 *  jcalc_exceptions.h
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Common exceptions for jcalc.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_EXCEPTIONS_H
#define PG_JCALC_EXCEPTIONS_H

#include <string>

namespace jcalc {

//  Base exception, all custom exceptions thrown by this module
//  are derived from CmdLineException

class jcalc_exception {
    private:
        std::string m_error_message;

    public:
        explicit jcalc_exception(const std::string& msg =
                                 "No error message")
            : m_error_message(msg) {}
        virtual ~jcalc_exception() {}

        const std::string& what() const { return m_error_message; }
};


//  Thrown when a backend does not support the requested output

class unsupported_output : public jcalc_exception {
    public:
        explicit unsupported_output(const std::string& output) :
            jcalc_exception("Backend does not support '" + output +
                            "' output.") {};
};

}           //  namespace jcalc

#endif      // PG_JCALC_EXCEPTIONS_H

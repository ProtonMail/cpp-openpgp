//
//  vinnie_folded_line_writer_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"


#include <ezvcard/io/folded_line_writer.hpp>

namespace tests {
    namespace ez_vcard_tests {
        using namespace vinnie;
        
        SUITE(vinnie_folded_line_writer_test)
        {
            /**
             * Asserts the writer's behavior without changing any settings.
             */
            TEST(default_settings) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                
                VERIFY_ARE_EQUAL(75, writer->getLineLength());
                VERIFY_ARE_EQUAL(" ", writer->getIndent());

                writer->write("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
                std::string actual = sw->str();
                auto expected =
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tem\r\n"
                " por incididunt ut labore et dolore magna aliqua.";
                
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            /**
             * The folding line length can be adjusted.
             */
            TEST(line_length) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(10);
                writer->write("Lorem ipsum dolor sit amet");
                
                auto actual = sw->str();
                auto expected =
                "Lorem ipsu\r\n"
                " m dolor s\r\n"
                " it amet";
                
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            /**
             * Setting the line length to "null" disables line folding.
             */
            TEST(line_length_null) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->disableLineLength();
                writer->write("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
                
                auto actual = sw->str();
                auto expected =
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
                
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            /**
             * When a newline sequence in the input string is encountered, this should
             * cause the line length to reset so that the next line can reach the max
             * line length.
             */
            TEST(line_length_reset_on_newline) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(10);
                writer->write("Lorem\r\nipsum dolor sit\ramet, consectetur\nadipiscing elit");
                auto actual = sw->str();
                auto expected =
                "Lorem\r\n"
                "ipsum dolo\r\n"
                " r sit\r"
                "amet, cons\r\n"
                " ectetur\n"
                "adipiscing \r\n"
                " elit";
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            /**
             * <p>
             * When the max line length has been reached, if the next character is a
             * space, the writer should temporarily exceed the max line length in order
             * to write the space on the same line before folding it. This is to prevent
             * the space character from being included with the folding whitespace of
             * the next line and possibly being ignored by the consuming application.
             * </p>
             * <p>
             * This is a possibility with old style syntax because old style syntax
             * allows multiple characters to be included in the folding whitespace. New
             * style syntax, by contrast, requires exactly one folding whitespace
             * character.
             * </p>
             */
            TEST(exceed_max_line_length_when_space_encountered) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(5);
                writer->write("Lorem ipsum dolor");
                auto actual = sw->str();
                auto expected =
                "Lorem \r\n" //exceed max line length temporarily
                " ipsu\r\n"
                " m do\r\n"
                " lor";
                VERIFY_ARE_EQUAL(expected, actual);
            }

            /**
             * Same as {@link #exceed_max_line_length_when_space_encountered} test, but
             * with the space character at the end of the string.
             */
            TEST(exceed_max_line_length_when_space_encountered_end_of_string) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(5);
                writer->write("Lorem ");
                auto actual = sw->str();
                auto expected =
                "Lorem ";
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            /**
             * The folding whitespace string can be changed.
             */
            TEST(indent) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setIndent("\t");
                writer->write("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
                auto actual = sw->str();
                auto expected =
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tem\r\n"
                "\tpor incididunt ut labore et dolore magna aliqua.";
                VERIFY_ARE_EQUAL(expected, actual);
            }

            TEST(quoted_printable) {
//                String input = "test \n\u00e4\u00f6\u00fc\u00df\n test";
//                Charset charset = Charset.forName("ISO-8859-1");
//                
//                StringWriter sw = new StringWriter();
//                FoldedLineWriter writer = new FoldedLineWriter(sw);
//                
//                writer.write(input, true, charset);
//                writer.close();
//                
//                String actual = sw.toString();
//                QuotedPrintableCodec codec = new QuotedPrintableCodec(charset.name());
//                String expectedOutput = codec.encode(input);
//                assertEquals(expectedOutput, actual);
            }

//            /**
//             * <p>
//             * When a quoted-printable encoded value is folded:
//             * </p>
//             * <ol>
//             * <li>Each line should end with a "=", except for the last line.</li>
//             * <li>No indent whitespace should be added to the folded lines.</li>
//             * <li>Max line length may be exceeded to ensure that no encoded character
//             * sequence spans multiple lines.</li>
//             * </ol>
//             */
//            @Test
//            public void quoted_printable_folded() throws Exception {
//                String input = "test \n\u00e4\u00f6\u00fc\u00df\n testing";
//                
//                StringWriter sw = new StringWriter();
//                FoldedLineWriter writer = new FoldedLineWriter(sw);
//                writer.setLineLength(10);
//                
//                writer.write(input, true, Charset.forName("ISO-8859-1"));
//                writer.write("\r\nthis line should be indented");
//                writer.close();
//                
//                String actual = sw.toString();
//                
//                //@formatter:off
//                String expected =
//                "test =0A=E4=\r\n" + //exceed max line length so encoded character does not span multiple lines
//                "=F6=FC=DF=\r\n" +
//                "=0A testi=\r\n" +
//                "ng\r\n" +
//                "this line \r\n" +
//                " should be \r\n" +
//                " indented";
//                //@formatter:on
//                
//                assertEquals(expected, actual);
//            }
//
//            /**
//             * Same as {@link #quoted_printable_folded} test, but when an encoded
//             * character ends the string.
//             */
//            @Test
//            public void quoted_printable_encoded_char_ends_the_string() throws Exception {
//                String input = "test\n";
//                
//                StringWriter sw = new StringWriter();
//                FoldedLineWriter writer = new FoldedLineWriter(sw);
//                writer.setLineLength(6);
//                
//                writer.write(input, true, Charset.forName("ISO-8859-1"));
//                writer.close();
//                
//                String actual = sw.toString();
//                
//                //@formatter:off
//                String expected =
//                "test=0A";
//                //@formatter:on
//                
//                assertEquals(expected, actual);
//            }
//            
//            /**
//             * Surrogate pairs should not be split across multiple lines.
//             */
//            @Test
//            public void surrogate_pair() throws Exception {
//                StringWriter sw = new StringWriter();
//                FoldedLineWriter writer = new FoldedLineWriter(sw);
//                writer.setLineLength(5);
//                
//                writer.write("test\uD83D\uDCF0test"); // should not be split
//                writer.close();
//                
//                String actual = sw.toString();
//                
//                //@formatter:off
//                String expected =
//                "test\uD83D\uDCF0\r\n" +
//                " test";
//                //@formatter:on
//                
//                assertEquals(expected, actual);
//            }
//            
//            /**
//             * Same as {@link #surrogate_pair} test, but with the surrogate pair at the
//             * end of the string.
//             */
//            @Test
//            public void surrogate_pair_ends_the_string() throws Exception {
//                StringWriter sw = new StringWriter();
//                FoldedLineWriter writer = new FoldedLineWriter(sw);
//                writer.setLineLength(5);
//                
//                writer.write("test\uD83D\uDCF0"); // should not be split
//                writer.close();
//                
//                String actual = sw.toString();
//                
//                //@formatter:off
//                String expected =
//                "test\uD83D\uDCF0";
//                //@formatter:on
//                
//                assertEquals(expected, actual);
//            }
            
            /**
             * Makes sure the writer takes character array sub-ranges into account.
             */
            TEST(write_sub_array) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(10);
                writer->write("This line should be folded.", 5, 14);
                
                auto actual = sw->str();
                auto expected =
                "line shoul\r\n"
                " d be";
                
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            TEST(writeln) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                
                writer->write("test");
                writer->writeln();
                
                auto actual = sw->str();
                auto expected =
                "test\r\n";
                
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
           TEST(getLineLength) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(10);
                VERIFY_ARE_EQUAL(10, writer->getLineLength());
            }
            
            TEST(setLineLength_zero) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                VERIFY_THROWS(writer->setLineLength(0), std::invalid_argument);
            }
            
            TEST(setLineLength_negative) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                VERIFY_THROWS(writer->setLineLength(-1), std::invalid_argument);
            }
            
            TEST(setLineLength_shorter_than_indent_length) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setIndent(" \t \t ");
                VERIFY_THROWS(writer->setLineLength(4), std::invalid_argument);
            }
            
            TEST(setLineLength_equal_to_indent_length) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setIndent(" \t \t ");
                VERIFY_THROWS(writer->setLineLength(5), std::invalid_argument);
            }
            
            TEST(getIndent) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setIndent("  ");
                VERIFY_ARE_EQUAL("  ", writer->getIndent());
            }
            
            TEST(setIndent_empty) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                VERIFY_THROWS(writer->setIndent(""), std::invalid_argument);
            }

            TEST(setIndent_longer_than_line_length) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(5);
                VERIFY_THROWS( writer->setIndent(" \t \t \t"), std::invalid_argument);
            }

            TEST(setIndent_equal_to_line_length) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->setLineLength(5);
                VERIFY_THROWS(writer->setIndent(" \t \t "), std::invalid_argument);
            }
            
            //exception shouldn't be thrown
            TEST(setIndent_with_null_line_length) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                writer->disableLineLength();
                writer->setIndent(" \t \t ");
            }
            
            TEST(setIndent_invalid_characters) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                VERIFY_THROWS(writer->setIndent("---"), std::invalid_argument);
            }

            TEST(getWriter) {
                auto sw = std::make_shared<std::stringstream>("");
                auto writer = std::make_shared<FoldedLineWriter>(sw);
                VERIFY_ARE_EQUAL(sw, writer->getWriter());
            }
        }
    }
}

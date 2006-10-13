// -*- C++ -*-
/*!
 * @file Properties.h
 * @brief Property list class (derived from Java Properties)
 * @date $Date: 2006-10-13 03:50:00 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Properties.h,v 1.2 2006-10-13 03:50:00 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:09:57  n-ando
 * Java compatible properties class.
 *
 *
 */

#ifndef Properties_h
#define Properties_h


#include <string>
#include <map>
#include <vector>


namespace RTC
{
  /*!
   * @if jp
   *
   * @class Properties
   *
   * Properties クラスは、不変のプロパティセットを表す。Properties をストリーム
   * に保管したり、ストリームからロードしたりすることができる。
   * プロパティリストの各キー、およびそれに対応する値は文字列となっている。
   *
   * プロパティリストには、その「デフォルト値」として別のプロパティリストを持つ
   * ことができる。元のプロパティリストでプロパティキーが見つからないと、この
   * 2番目のプロパティリストが検索される。 
   *
   * Properties は std::map<std::string, std:string> を継承するので、std::map
   * が持つメソッドを適用することができる。しかし、これらのメソッドを使用する
   * ことは推奨されない。
   * プロパティの取得には getProperty、プロパティのセットには setProperty と
   * いったメソッドを使用することが推奨される。
   *
   * プロパティをストリームに保存するとき、またはストリームからロードするときに、
   * ISO 8859-1 文字エンコーディングが使用される。このエンコーディングに直接表示
   * できない文字は、扱うことができない。
   *
   * このクラスは、Java の Properties クラス (java.util.Properties) とほぼ同様の
   * メソッドを持つ。また、入出力されるファイルは Java の Properties クラスが
   * 出力するものと互換性があるが、Unicode を含むものは扱うことができない。
   *
   * @else
   *
   * @class Properties
   *
   * The Properties class represents a persistent set of properties. The
   * Properties can be saved to a stream or loaded from a stream. Each key and
   * its corresponding value in the property list is a string. 
   *
   * A property list can contain another property list as its "defaults"; this
   * second property list is searched if the property key is not found in the
   * original property list. 
   *
   * Because Properties inherits from Hashtable, the put and putAll methods can
   * be applied to a Properties object. Their use is strongly discouraged as they
   * allow the caller to insert entries whose keys or values are not Strings. The
   * setProperty method should be used instead. If the store or save method is
   * called on a "compromised" Properties object that contains a non-String key
   * or value, the call will fail. 
   *
   * The load and store methods load and store properties in a simple
   * line-oriented format specified below. This format uses the ISO 8859-1
   * character encoding. Characters that cannot be directly represented in this
   * encoding can be written using Unicode escapes ; only a single 'u' character
   * is allowed in an escape sequence. The native2ascii tool can be used to
   * convert property files to and from other character encodings. 
   *
   * This class has almost same methods of Java's Properties class. Input and 
   * Output stream of this properties are compatible each other except Unicode
   * encoded property file.
   *
   * @endif
   */
  class Properties
    : public std::map<std::string, std::string>
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * デフォルト値を持たない空のプロパティリストを作成する。
     * 
     * @else
     *
     * @brief Constructor
     *
     * Creates an empty property list with no default values.
     *
     * @endif
     */
    Properties(){};
    
    
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * 指定されたデフォルト値を持つ空のプロパティリストを作成する。
     * 
     * @else
     *
     * @brief Constructor
     *
     * Creates an empty property list with the specified defaults.
     *
     * @endif
     */
    Properties(const std::map<std::string, std::string>& defaults);
    
    
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * 指定されたデフォルト値を持つ空のプロパティリストを作成する。
     * デフォルト値は char* の配列により与えられ、key と value の対になっており、
     * リストの終端は配列の数を表す引数 num か、空文字の key で与えらられなければ
     * ならない。
     * 以下に例を示す。
     *
     * const char* defaults = {
     *     "key1", "value1",
     *     "key2", "value2",
     *     "key3", "value3",
     *     "key4", "value4",
     *     "key5", "value5",
     *     "" };
     * Properties p(defaults);
     * // もしくは
     * Properties p(defaults, 10);
     * 
     * @else
     *
     * @brief Constructor
     *
     * Creates an empty property list with the specified defaults.
     * The default values are given by array of char*, which should be pairs
     * of "key" and "value". The end of list is specified by argument "num",
     * which specifies number of array or null character of key.
     * The following is an example.
     *
     * const char* defaults = {
     *     "key1", "value1",
     *     "key2", "value2",
     *     "key3", "value3",
     *     "key4", "value4",
     *     "key5", "value5",
     *     "" };
     * Properties p(defaults);
     * // or
     * Properties p(defaults, 10);
     *
     * @endif
     */
    Properties(const char* defaults[], long num = LONG_MAX);
    
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~Properties();
    
    
    /*!
     * @if jp
     *
     * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
     *
     * 指定されたキーを持つプロパティを、プロパティリストから探す。
     * そのキーがプロパティリストにないと、デフォルトのプロパティリスト、
     * さらにそのデフォルト値が繰り返し調べられる。
     * そのプロパティが見つからない場合は、null が返される。 
     *
     * @param key プロパティキー
     * @return 指定されたキー値を持つこのプロパティリストの値
     *
     * @else
     *
     * @brief Searches for the property with the specified key in this property
     *
     * Searches for the property with the specified key in this property list.
     * If the key is not found in this property list, the default property list,
     * and its defaults, recursively, are then checked. The method returns null
     * if the property is not found. 
     *
     * @param key the property key.
     * @return the value in this property list with the specified key value.
     *
     * @endif
     */
    std::string getProperty(const std::string& key);
    
    /*!
     * @if jp
     *
     * @brief 指定されたキーを持つプロパティを、プロパティリストから探す。 
     *
     * 指定されたキーを持つプロパティを、プロパティリストから探す。
     * そのキーがプロパティリストにないと、デフォルトのプロパティリスト、
     * さらにそのデフォルト値が繰り返し調べられる。
     * そのプロパティが見つからない場合は、デフォルト値の引数が返される。 
     *
     * @param key プロパティキー
     * @param defaultValue デフォルト値
     * @return 指定されたキー値を持つこのプロパティリストの値
     *
     * @else
     *
     * @brief Searches for the property with the specified key in this property
     *
     * Searches for the property with the specified key in this property list.
     * If the key is not found in this property list, the default property list,
     * and its defaults, recursively, are then checked. The method returns the
     * default value argument if the property is not found.
     *
     * @param key the property key
     * @param defaultValue a default value. 
     * @return the value in this property list with the specified key value.
     *
     * @endif
     */
    std::string getProperty(const std::string& key,
			    const std::string& defaultValue);
    
    /*!
     * @if jp
     *
     * @brief 指定された出力ストリームに、プロパティリストを出力する
     *
     * 指定された出力ストリームに、プロパティリストを出力する。
     * このメソッドは主にデバッグに用いられる。
     *
     * @param out 出力ストリーム
     *
     * @else
     *
     * @brief Prints this property list out to the specified output stream
     *
     * Prints this property list out to the specified output stream.
     * This method is useful for debugging.
     *
     * @param out an output stream.
     *
     * @endif
     */
    void list(std::ostream& out);
    
    
    /*!
     * @if jp
     *
     * @brief 入力ストリームからキーと要素が対になったプロパティリストを読み込む
     *
     * 入力ストリームからキーと要素が対になったプロパティリストを読み込む。
     * ストリームは、ISO 8859-1 文字エンコーディングを使用しているとみなされる。
     * 各プロパティは、入力ストリームに行単位で登録されているものとみなされ、
     * 各行は行区切り文字 (\n、\r、または \r\n) で終わる。
     * 入力ストリームから読み込んだ行は、入力ストリームでファイルの終わりに
     * 達するまで処理される。
     *
     * 空白文字だけの行、または最初の非空白文字が ASCII 文字 # または ! である
     * 行は無視される。つまり、# または ! はコメント行を示す。
     *
     * 空白行またはコメント行以外のすべての行は、テーブルに追加されるプロパティ
     * を記述する。ただし、行の終わりが \ の場合は、次の行があれば継続行として
     * 扱われます (下記を参照)。 キーは、最初の非空白文字から、最初の ASCII 文字
     * =、:、または空白文字の直前までの、行内のすべての文字から構成される。
     *
     * キーの終わりを示す文字は、前に \ を付けることによりキーに含めることも
     * できる。キーの後ろの空白はすべてスキップされる。
     * キーの後ろの最初の非空白文字が = または : である場合は、これらのキーは
     * 無視され、そのあとの空白文字もすべてスキップされる。
     * 行内のそれ以外の文字はすべて、関連した要素文字列の一部となる。
     * 要素文字列内では、ASCII エスケープシーケンス \t、\n、\r、\\、\"、\'、
     * \ (円記号とスペース)、および \uxxxx は認識され、単独の文字に変換される。
     * また、行の最後の文字が \ である場合は、次の行は現在の行の継続として
     * 扱われる。その場合、\ と行区切り文字が破棄され、継続行の先頭に空白が
     * あればそれもすべて破棄され、要素文字列の一部にはならない。 
     *
     * たとえば、次の 4 行はそれぞれキー Truth と、関連した要素値 Beauty を表す。
     * 
     * Truth = Beauty <BR>
     *	Truth:Beauty <BR>
     * Truth			:Beauty <BR>
     *
     * また、次の 3 行は 1 つのプロパティを表す。 
     *
     * fruits				apple, banana, pear, \ <BR>
     *                                  cantaloupe, watermelon, \ <BR>
     *                                  kiwi, mango <BR>
     * キーは fruits で、次の要素に関連付けれられる。 
     * "apple, banana, pear, cantaloupe, watermelon, kiwi, mango"
     * 最終的な結果でコンマのあとに必ずスペースが表示されるように、
     * 各 \ の前にスペースがある。行の終わりを示す \ と、継続行の先頭にある
     * 空白は破棄され、他の文字に置換されない。 
     * また、次の 3 番目の例では、キーが cheeses で、関連した要素が空の文字列
     * であることを表す。 
     *
     * cheeses <BR>
     * キーは、cheeses で、関連要素は空の文字列であることを指定している。 
     *
     * @param inStream 入力ストリーム 
     *
     * @else
     *
     * @brief Loads property list consists of key:value from input stream
     *
     * Reads a property list (key and element pairs) from the input stream.
     * The stream is assumed to be using the ISO 8859-1 character encoding; that
     * is each byte is one Latin1 character. Characters not in Latin1, and
     * certain special characters, can be represented in keys and elements using
     * escape sequences similar to those used for character and string literals
     * The differences from the character escape sequences used for characters
     * and strings are: 
     * - Octal escapes are not recognized. 
     * - The character sequence \b does not represent a backspace character. 
     * - The method does not treat a backslash character, \, before a non-valid
     *   escape character as an error; the backslash is silently dropped. For
     *   example, in a Java string the sequence "\z" would cause a compile time
     *   error. In contrast, this method silently drops the backslash. Therefore,
     *   this method treats the two character sequence "\b" as equivalent to the
     *   single character 'b'. 
     * - Escapes are not necessary for single and double quotes; however, by the
     *   rule above, single and double quote characters preceded by a backslash
     *   still yield single and double quote characters, respectively. 
     * An IllegalArgumentException is thrown if a malformed Unicode escape
     * appears in the input. 
     *
     * This method processes input in terms of lines. A natural line of input is
     * terminated either by a set of line terminator characters
     * (\n or \r or \r\n) or by the end of the file. A natural line may be either
     * a blank line, a comment line, or hold some part of a key-element pair.
     * The logical line holding all the data for a key-element pair may be spread
     * out across several adjacent natural lines by escaping the line terminator
     * sequence with a backslash character, \. Note that a comment line cannot be
     * extended in this manner; every natural line that is a comment must have
     * its own comment indicator, as described below. If a logical line is
     * continued over several natural lines, the continuation lines receive
     * further processing, also described below. Lines are read from the input
     * stream until end of file is reached. 
     *
     * A natural line that contains only white space characters is considered
     * blank and is ignored. A comment line has an ASCII '#' or '!' as its first
     * non-white space character; comment lines are also ignored and do not
     * encode key-element information. In addition to line terminators, this
     * method considers the characters space (' ', '\u0020'), tab 
     * ('\t', '\u0009'), and form feed ('\f', '\u000C') to be white space. 
     *
     * If a logical line is spread across several natural lines, the backslash
     * escaping the line terminator sequence, the line terminator sequence, and
     * any white space at the start the following line have no affect on the key
     * or element values. The remainder of the discussion of key and element
     * parsing will assume all the characters constituting the key and element
     * appear on a single natural line after line continuation characters have
     * been removed. Note that it is not sufficient to only examine the character
     * preceding a line terminator sequence to see if the line terminator is
     * escaped; there must be an odd number of contiguous backslashes for the
     * line terminator to be escaped. Since the input is processed from left to
     * right, a non-zero even number of 2n contiguous backslashes before a line
     * terminator (or elsewhere) encodes n backslashes after escape processing. 
     *
     * The key contains all of the characters in the line starting with the first
     * non-white space character and up to, but not including, the first
     * unescaped '=', ':', or white space character other than a line terminator.
     * All of these key termination characters may be included in the key by
     * escaping them with a preceding backslash character; for example,
     *
     * \:\=
     *
     * would be the two-character key ":=". Line terminator characters can be
     * included using \r and \n escape sequences. Any white space after the key
     * is skipped; if the first non-white space character after the key is '=' or
     * ':', then it is ignored and any white space characters after it are also
     * skipped. All remaining characters on the line become part of the
     * associated element string; if there are no remaining characters, the
     * element is the empty string "". Once the raw character sequences
     * constituting the key and element are identified, escape processing is
     * performed as described above. 
     *
     * As an example, each of the following three lines specifies the key "Truth"
     * and the associated element value "Beauty": 
     *
     * Truth = Beauty <BR>
     *        Truth:Beauty <BR>
     * Truth                  :Beauty <BR>
     *  As another example, the following three lines specify a single property: 
     *
     * fruits                           apple, banana, pear, \ <BR>
     *                                  cantaloupe, watermelon, \ <BR>
     *                                  kiwi, mango <BR>
     * The key is "fruits" and the associated element is: 
     * "apple, banana, pear, cantaloupe, watermelon, kiwi, mango"Note that a
     * space appears before each \ so that a space will appear after each comma
     * in the final result; the \, line terminator, and leading white space on
     * the continuation line are merely discarded and are not replaced by one or
     * more other characters. 
     * As a third example, the line: 
     *
     * cheeses <BR>
     * specifies that the key is "cheeses" and the associated element is the
     * empty string "".
     *
     * @param inStream the input stream.
     *
     * @endif
     */
    void load(std::istream& inStream);
    
    
    /*!
     * @if jp
     *
     * @brief プロパティのキーのリストを vector で返す
     *
     * メインプロパティリストに同じ名前のキーが見つからない場合は、デフォルトの
     * プロパティリストにある個別のキーを含む、このプロパティリストにあるすべて
     * のキーのリストを返します。 
     *
     * @return プロパティリストにあるすべてのキーのリスト。
     *         デフォルトのプロパティリストにあるキーを含む
     *
     * @else
     *
     * @brief Returns an vector of all the keys in this property
     *
     * Returns an enumeration of all the keys in this property list, including
     * distinct keys in the default property list if a key of the same name has
     * not already been found from the main properties list.
     *
     * @return an vector of all the keys in this property list, including the
     *         keys in the default property list.
     *
     * @endif
     */
    std::vector<std::string> propertyNames();
    
    
    /*!
     * @if jp
     *
     * @brief プロパティリストを指定されたストリームに保存する
     *
     * 推奨されていません。プロパティリストの保存方法としては、
     * store(ostream out, string header) メソッドの使用が推奨される。
     * このメソッドは Java Properties との互換性のために定義されている。
     *
     * @param out 出力ストリーム
     * @param header プロパティリストの記述 
     *
     * @else
     *
     * @brief Save the properties list to the stream
     *
     * Deprecated. 
     *
     * @param out The output stream
     * @param header A description of the property list
     *
     * @endif
     */
    void save(std::ostream& out, const std::string& header);
    
    
    /*!
     * @if jp
     *
     * @brief Properties に value を key について登録する
     *
     * Properties に value を key について登録する。
     * すでに key に対する値を持っている場合、戻り値に古い値を返す。
     *
     * @param key プロパティリストに配置されるキー
     * @param value key に対応する値 
     * @return プロパティリストの指定されたキーの前の値。それがない場合は null
     *
     * @else
     *
     * @brief Sets a value associated with key in the property list
     *
     * This method sets the "value" associated with "key" in the property list.
     * If the property list has a value of "key", old value is returned.
     *
     * @param key the key to be placed into this property list.
     * @param value the value corresponding to key. 
     * @return the previous value of the specified key in this property list,
     *         or null if it did not have one.
     *
     *@endif
     */
    std::string setProperty(const std::string& key, const std::string& value);
    
    
    /*!
     * @if jp
     *
     * @brief プロパティリストを出力ストリームへ保存する
     *
     * Properties テーブル内のプロパティリスト (キーと要素のペア) を、load
     * メソッドを使って Properties テーブルにロードするのに適切なフォーマットで
     * 出力ストリームに書き込みます。 
     *
     * Properties テーブル内のプロパティリスト (キーと要素のペア) を、load
     * メソッドを使って Properties テーブルにロードするのに適切なフォーマットで
     * 出力ストリームに書き込みます。ストリームは、ISO 8859-1 文字
     * エンコーディングを使用して書き込まれます。 
     * Properties テーブル (存在する場合) のデフォルトテーブルからの
     * プロパティは、このメソッドによっては書き込まれません。 
     *
     * header 引数が null でない場合は、ASCII 文字の #、header の文字列、
     * および行区切り文字が最初に出力ストリームに書き込まれます。このため、
     * header は識別コメントとして使うことができます。 
     *
     * 次に、ASCII 文字の #、現在の日時 (Date の toString メソッドによって
     * 現在時刻が生成されるのと同様)、および Writer によって生成される行区切り
     * からなるコメント行が書き込まれます。 
     *
     * 続いて、Properties テーブル内のすべてのエントリが 1 行ずつ書き出されます。
     * 各エントリのキー文字列、ASCII 文字の =、関連した要素文字列が書き込まれま
     * す。要素文字列の各文字は、エスケープシーケンスとして描画する必要があるか
     * どうか確認されます。ASCII 文字の \、タブ、改行、および復帰はそれぞれ \\、
     * \t、\n、および \r として書き込まれます。\u0020 より小さい文字および
     * \u007E より大きい文字は、対応する 16 進値 xxxx を使って \uxxxx として書き
     * 込まれます。埋め込み空白文字でも後書き空白文字でもない先行空白文字は、
     * 前に \ を付けて書き込まれます。キーと値の文字 #、!、=、および : は、
     * 必ず正しくロードされるように、前にスラッシュを付けて書き込まれます。 
     *
     * エントリが書き込まれたあとで、出力ストリームがフラッシュされます。
     * 出力ストリームはこのメソッドから復帰したあとも開いたままです。 
     *
     * @else
     *
     * @brief Stores property list to the output stream
     *
     * Writes this property list (key and element pairs) in this Properties table
     * to the output stream in a format suitable for loading into a Properties
     * table using the load method. The stream is written using the ISO 8859-1
     * character encoding. 
     *
     * Properties from the defaults table of this Properties table (if any) are
     * not written out by this method. 
     *
     * If the comments argument is not null, then an ASCII # character, the
     * comments string, and a line separator are first written to the output
     * stream. Thus, the comments can serve as an identifying comment. 
     *
     * Next, a comment line is always written, consisting of an ASCII #
     * character, the current date and time (as if produced by the toString
     * method of Date for the current time), and a line separator as generated
     * by the Writer. 
     *
     * Then every entry in this Properties table is written out, one per line.
     * For each entry the key string is written, then an ASCII =, then the
     * associated element string. Each character of the key and element strings
     * is examined to see whether it should be rendered as an escape sequence.
     * The ASCII characters \, tab, form feed, newline, and carriage return are
     * written as \\, \t, \f \n, and \r, respectively. Characters less than
     * \u0020 and characters greater than \u007E are written as \uxxxx for the
     * appropriate hexadecimal value xxxx. For the key, all space characters are
     * written with a preceding \ character. For the element, leading space
     * characters, but not embedded or trailing space characters, are written
     * with a preceding \ character. The key and element characters #, !, =, and
     * : are written with a preceding backslash to ensure that they are properly
     * loaded. 
     *
     * After the entries have been written, the output stream is flushed. The
     * output stream remains open after this method returns. 
     *
     * @param out an output stream.
     * @param header a description of the property list.
     *
     * @endif
     */
    void store(std::ostream& out, const std::string& header);
    
  protected:
    void eraseHeadBlank(std::string& str);
    void eraseTailBlank(std::string& str);
    void replaceStr(std::string& str, const std::string from,
		    const std::string to);
    //  void replaceEscape(std::string& str);
    void splitKeyValue(const std::string& str, std::string& key,
		       std::string& value);
    
    std::map<std::string, std::string> m_defaults;
    typedef std::map<std::string, std::string>::iterator Itr;
    
  };   // class Properties
};     // namespace RTC  
#endif // Properties_h
  

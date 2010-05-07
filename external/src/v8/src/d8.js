// Copyright 2008 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.




function MakeJSONPair_(name, value) {
  return '"' + name + '":' + value;
}


function ArrayToJSONObject_(content) {
  return '{' + content.join(',') + '}';
}


function ArrayToJSONArray_(content) {
  return '[' + content.join(',') + ']';
}


function BooleanToJSON_(value) {
  return String(value); 
}


function NumberToJSON_(value) {
  return String(value); 
}


// Mapping of some control characters to avoid the \uXXXX syntax for most
// commonly used control cahracters.
const ctrlCharMap_ = {
  '\b': '\\b',
  '\t': '\\t',
  '\n': '\\n',
  '\f': '\\f',
  '\r': '\\r',
  '"' : '\\"',
  '\\': '\\\\'
};


// Regular expression testing for ", \ and control characters (0x00 - 0x1F).
const ctrlCharTest_ = new RegExp('["\\\\\x00-\x1F]');


// Regular expression matching ", \ and control characters (0x00 - 0x1F)
// globally.
const ctrlCharMatch_ = new RegExp('["\\\\\x00-\x1F]', 'g');


/**
 * Convert a String to its JSON representation (see http://www.json.org/). To
 * avoid depending on the String object this method calls the functions in
 * string.js directly and not through the value.
 * @param {String} value The String value to format as JSON
 * @return {string} JSON formatted String value
 */
function StringToJSON_(value) {
  // Check for" , \ and control characters (0x00 - 0x1F). No need to call
  // RegExpTest as ctrlchar is constructed using RegExp.
  if (ctrlCharTest_.test(value)) {
    // Replace ", \ and control characters (0x00 - 0x1F).
    return '"' +
      value.replace(ctrlCharMatch_, function (char) {
        // Use charmap if possible.
        var mapped = ctrlCharMap_[char];
        if (mapped) return mapped;
        mapped = char.charCodeAt();
        // Convert control character to unicode escape sequence.
        return '\\u00' +
          '0' + // TODO %NumberToRadixString(Math.floor(mapped / 16), 16) +
          '0' // TODO %NumberToRadixString(mapped % 16, 16);
      })
    + '"';
  }

  // Simple string with no special characters.
  return '"' + value + '"';
}


/**
 * Convert a Date to ISO 8601 format. To avoid depending on the Date object
 * this method calls the functions in date.js directly and not through the
 * value.
 * @param {Date} value The Date value to format as JSON
 * @return {string} JSON formatted Date value
 */
function DateToISO8601_(value) {
  function f(n) {
    return n < 10 ? '0' + n : n;
  }
  function g(n) {
    return n < 10 ? '00' + n : n < 100 ? '0' + n : n;
  }
  return builtins.GetUTCFullYearFrom(value)         + '-' +
          f(builtins.GetUTCMonthFrom(value) + 1)    + '-' +
          f(builtins.GetUTCDateFrom(value))         + 'T' +
          f(builtins.GetUTCHoursFrom(value))        + ':' +
          f(builtins.GetUTCMinutesFrom(value))      + ':' +
          f(builtins.GetUTCSecondsFrom(value))      + '.' +
          g(builtins.GetUTCMillisecondsFrom(value)) + 'Z';
}


/**
 * Convert a Date to ISO 8601 format. To avoid depending on the Date object
 * this method calls the functions in date.js directly and not through the
 * value.
 * @param {Date} value The Date value to format as JSON
 * @return {string} JSON formatted Date value
 */
function DateToJSON_(value) {
  return '"' + DateToISO8601_(value) + '"';
}


/**
 * Convert an Object to its JSON representation (see http://www.json.org/).
 * This implementation simply runs through all string property names and adds
 * each property to the JSON representation for some predefined types. For type
 * "object" the function calls itself recursively unless the object has the
 * function property "toJSONProtocol" in which case that is used. This is not
 * a general implementation but sufficient for the debugger. Note that circular
 * structures will cause infinite recursion.
 * @param {Object} object The object to format as JSON
 * @return {string} JSON formatted object value
 */
function SimpleObjectToJSON_(object) {
  var content = [];
  for (var key in object) {
    // Only consider string keys.
    if (typeof key == 'string') {
      var property_value = object[key];

      // Format the value based on its type.
      var property_value_json;
      switch (typeof property_value) {
        case 'object':
          if (typeof property_value.toJSONProtocol == 'function') {
            property_value_json = property_value.toJSONProtocol(true)
          } else if (property_value.constructor.name == 'Array'){
            property_value_json = SimpleArrayToJSON_(property_value);
          } else {
            property_value_json = SimpleObjectToJSON_(property_value);
          }
          break;

        case 'boolean':
          property_value_json = BooleanToJSON_(property_value);
          break;

        case 'number':
          property_value_json = NumberToJSON_(property_value);
          break;

        case 'string':
          property_value_json = StringToJSON_(property_value);
          break;

        default:
          property_value_json = null;
      }

      // Add the property if relevant.
      if (property_value_json) {
        content.push(StringToJSON_(key) + ':' + property_value_json);
      }
    }
  }

  // Make JSON object representation.
  return '{' + content.join(',') + '}';
}


/**
 * Convert an array to its JSON representation. This is a VERY simple
 * implementation just to support what is needed for the debugger.
 * @param {Array} arrya The array to format as JSON
 * @return {string} JSON formatted array value
 */
function SimpleArrayToJSON_(array) {
  // Make JSON array representation.
  var json = '[';
  for (var i = 0; i < array.length; i++) {
    if (i != 0) {
      json += ',';
    }
    var elem = array[i];
    if (elem.toJSONProtocol) {
      json += elem.toJSONProtocol(true)
    } else if (typeof(elem) === 'object')  {
      json += SimpleObjectToJSON_(elem);
    } else if (typeof(elem) === 'boolean')  {
      json += BooleanToJSON_(elem);
    } else if (typeof(elem) === 'number')  {
      json += NumberToJSON_(elem);
    } else if (typeof(elem) === 'string')  {
      json += StringToJSON_(elem);
    } else {
      json += elem;
    }
  }
  json += ']';
  return json;
}

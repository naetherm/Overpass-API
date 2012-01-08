#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "cgi-helper.h"

using namespace std;

char hex_digit(char c)
{
  if (c <= 57)
  {
    if (c >= 48)
      return c - 48;
    return 16;
  }
  if (c <= 70)
  {
    if (c >= 65)
      return c - 55;
    return 16;
  }
  if (c <= 102)
  {
    if (c >= 97)
      return c - 87;
    return 16;
  }
  return 16;
}

string cgi_get_to_text()
{
  char* method;
  method = getenv("REQUEST_METHOD");
  if ((method) && (!strcmp(method, "GET")))
    return getenv("QUERY_STRING");
  
  return "";
}

string cgi_post_to_text()
{
  string raw, buf;
  while (!cin.eof())
  {
    getline(cin, buf);
    raw += buf + '\n';
  }
  return raw;
}

string decode_cgi_to_plain(const string& raw, int& error, string& jsonp)
{
  error = 0;
  string result;
  string::size_type pos(raw.find("data="));
  if ((pos >= raw.size()) || (pos == string::npos))
  {
    error = 1;
    return "";
  }
  pos += 5;
  
  while (pos < raw.size())
  {
    if (raw[pos] == '%')
    {
      if (pos >= raw.size()+2)
	return (result + raw.substr(0, pos));
      char a(hex_digit(raw[pos+1])), b(hex_digit(raw[pos+2]));
      if ((a < 16) && (b < 16))
      {
	result += (char)(a*16 + b);
	pos += 3;
      }
      else
	result += raw[pos++];
    }
    else if (raw[pos] == '+')
    {
      result += ' ';
      ++pos;
    }
    else if (raw[pos] == '&')
      pos = raw.size();
    else
      result += raw[pos++];
  }
  
  pos = raw.find("jsonp=");
  if (pos != string::npos)
  {
    string::size_type endpos = raw.find('&', pos);
    if (endpos == string::npos)
      jsonp = raw.substr(pos + 6);
    else
      jsonp = raw.substr(pos + 6, endpos - pos - 6);
  }
  
  return result;
}

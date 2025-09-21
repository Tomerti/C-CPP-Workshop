#include "cipher.h"
#include <ctype.h>
#include <string.h>

#define AU_ASCII (65)
#define ZU_ASCII (90)
#define AL_ASCII (97)
#define ZL_ASCII (122)
#define ASCII_LETTERS (26)

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


// See full documentation in header file
/**
 * Encodes a lower case letter.
 * @param s address to lower case letter.
 * @param k given k parameter used for encoding.
 */
void encode_lower(char *s, int k)
{
    int tempnum = *s + k;
    if (tempnum > ZL_ASCII)
    {
        tempnum = (AL_ASCII - 1) + (tempnum - ZL_ASCII);
    }
    if (tempnum < AL_ASCII)
    {
        if(k>=0)
        {
            tempnum = (AL_ASCII - 1) + (AL_ASCII - tempnum);
        }
        else
        {
            tempnum = (ZL_ASCII + 1) - (AL_ASCII - tempnum);
        }
    }
    *s = tempnum;
}

/**
 * Encodes an upper case letter.
 * @param s address to upper case letter.
 * @param k given k parameter used for encoding.
 */
void encode_upper(char *s, int k)
{
    int tempnum = *s + k;
    if (tempnum > ZU_ASCII)
    {
        tempnum = (AU_ASCII - 1) + (tempnum - ZU_ASCII);
    }
    if (tempnum < AU_ASCII)
    {
        if(k>=0)
        {
            tempnum = (AU_ASCII - 1) + (AU_ASCII - tempnum);
        }
        else
        {
            tempnum = (ZU_ASCII + 1) - (AU_ASCII - tempnum);
        }
    }
    *s = tempnum;
}

// See full documentation in header file
void encode (char s[], int k)
{
  // your code goes here
  int fixed_k = k%ASCII_LETTERS;
  unsigned int i = 0;
  for(;i<strlen(s);i++)
  {
      if(islower(s[i]))
      {
          encode_lower(&s[i],fixed_k);
      }
      if(isupper(s[i]))
      {
          encode_upper(&s[i],fixed_k);
      }
  }
}

// See full documentation in header file
void decode (char s[], int k)
{
  // your code goes here
  int fixed_k = k%ASCII_LETTERS;
  unsigned int i = 0;
  for(;i<strlen(s);i++)
  {
      if (islower(s[i]))
      {
          encode_lower(&s[i],-fixed_k);
      }
      if(isupper(s[i]))
      {
          encode_upper(&s[i],-fixed_k);
      }
  }
}

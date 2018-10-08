#define MDOT_TIME (100)
#define MDASH_TIME (300)
#define M_PAUSE (MDASH_TIME)
#define MLED 13


#define UNIT_LENGTH    250

//Build a struct with the morse code mapping
static const struct {const char letter, *code;} MorseMap[] =
{
    { 'A', ".-" },
    { 'B', "-..." },
    { 'C', "-.-." },
    { 'D', "-.." },
    { 'E', "." },
    { 'F', "..-." },
    { 'G', "--." },
    { 'H', "...." },
    { 'I', ".." },
    { 'J', ".---" },
    { 'K', ".-.-" },
    { 'L', ".-.." },
    { 'M', "--" },
    { 'N', "-." },
    { 'O', "---" },
    { 'P', ".--." },
    { 'Q', "--.-" },
    { 'R', ".-." },
    { 'S', "..." },
    { 'T', "-" },
    { 'U', "..-" },
    { 'V', "...-" },
    { 'W', ".--" },
    { 'X', "-..-" },
    { 'Y', "-.--" },
    { 'Z', "--.." },
    { ' ', "     " }, //Gap between word, seven units 
        
    { '1', ".----" },
    { '2', "..---" },
    { '3', "...--" },
    { '4', "....-" },
    { '5', "....." },
    { '6', "-...." },
    { '7', "--..." },
    { '8', "---.." },
    { '9', "----." },
    { '0', "-----" },
        
    { '.', "·–·–·–" },
    { ',', "--..--" },
    { '?', "..--.." },
    { '!', "-.-.--" },
    { ':', "---..." },
    { ';', "-.-.-." },
    { '(', "-.--." },
    { ')', "-.--.-" },
    { '"', ".-..-." },
    { '@', ".--.-." },
    { '&', ".-..." },
};

void setup()
{
  Serial.begin(9600);
  pinMode( MLED, OUTPUT );
  digitalWrite( MLED, LOW );
}

void loop()
{
  
  Serial.println("Enter your text: ");
 	while (Serial.available()==0) {             //Wait for user input
  
  }
  String text =  Serial.readString();
  String morseWord = encode(text);
    
  for(int i=0; i<=morseWord.length(); i++)
  {
    switch( morseWord[i] )
    {
      case '.': //dit
        digitalWrite( MLED, HIGH );
        delay( UNIT_LENGTH );
        digitalWrite( MLED, LOW );
        delay( UNIT_LENGTH );
          
        break;

      case '-': //dah
        digitalWrite( MLED, HIGH );
        delay( UNIT_LENGTH*3 );
        digitalWrite( MLED, LOW );
        delay( UNIT_LENGTH );
          
        break;

      case ' ': //gap
        delay( UNIT_LENGTH );
    }
  }
}

String encode(String string)
{
  size_t i, j;
  String morseWord = "";
  
  for( i = 0; string[i]; ++i )
  {
    for( j = 0; j < sizeof MorseMap / sizeof *MorseMap; ++j )
    {
      if( toupper(string[i]) == MorseMap[j].letter )
      {
        morseWord += MorseMap[j].code;
        break;
      }
    }
    morseWord += " "; //Add tailing space to seperate the chars
  }

  return morseWord;  
}

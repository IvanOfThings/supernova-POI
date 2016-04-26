// This sketch shows how to sequence a performance using HH,MM,SS.SSS timecode.
//
// A "ResetPerformance" method is provided so that the performance can be
// restarted from a custom external trigger, e.g., a button or event.
//
// -Mark Kriegsman, January 2015

uint32_t gTimeCode             = 0,
         gTimeCodeBase         = 0,
         gLastTimeCodeDoneAt   = 0,
         gLastTimeCodeDoneFrom = 0;
 
#define TC(HOURS,MINUTES,SECONDS) \
 ((HOURS)*3600000L + (MINUTES)*60000L + (SECONDS)*1000L)
#define AT(HOURS,MINUTES,SECONDS)   if(atTC(TC(HOURS,MINUTES,SECONDS)))
#define FROM(HOURS,MINUTES,SECONDS) if(fromTC(TC(HOURS,MINUTES,SECONDS)))

static bool atTC(uint32_t tc) {
  if(gTimeCode >= tc) {
    if(gLastTimeCodeDoneAt < tc) {
      gLastTimeCodeDoneAt = tc;
      return true;
    }
  }
  return false;
}
 
static bool fromTC(uint32_t tc) {
  if(gTimeCode >= tc) {
    if(gLastTimeCodeDoneFrom <= tc) {
      gLastTimeCodeDoneFrom = tc;
      return true;
    }
  }
  return false;
}
 
// There are two kinds of things you can put into this performance:
// "FROM" and "AT".
//
// * "FROM" means starting FROM this time AND CALLING IT REPEATEDLY
//   until the next "FROM" time comes.
//
// * "AT" means do this ONE TIME ONLY "AT" the designated time.
//
// At least one of the FROM clauses will ALWAYS be executed.
// In the transitional times, TWO pieces of code will be executed back to back.
// For example, if one piece says "FROM(0,0,1.000) {DrawRed()}" and another says
// "FROM(0,0,2.000) {flashblue();}", what you'll get is this:
//   00:00:01.950  -> calls DrawRed
//   00:00:01.975  -> calls DrawRed
//   00:00:02.000  -> calls DrawRed AND calls DrawBlue !
//   00:00:02.025  -> calls DrawBlue
//   00:00:02.050  -> calls DrawBlue
// In most cases, this probably isn't significant in practice, but it's important
// to note.  It could be avoided by listing the sequence steps in reverse
// chronological order, but that makes it hard to read.


void Performance() {
  gTimeCode = millis() - gTimeCodeBase;

  AT(0,0,00.100)   { setImage(46); }  //music
  AT(0,0,12.080)   { setImage(41); }
  AT(0,0,24.110)   { setImage(42); }
  AT(0,0,30.130)   { setImage(43); }
  AT(0,0,36.360)   { setImage(28); }
  AT(0,0,48.280)   { setImage(31); }
  AT(0,0,54.320)   { setImage(44); }
  AT(0,0,57.300)   { setImage(45); }
  AT(0,1,00.300)   { setImage(46); }
  
  AT(0,1,12.400)   { setImage(41); }
  AT(0,1,18.380)   { setImage(42); }
  AT(0,1,25.020)   { setImage(43); }
  AT(0,1,31.043)   { setImage(50); }
  AT(0,1,37.100)   { setImage(28); }
  AT(0,1,49.350)   { setImage(31); }
  AT(0,1,55.320)   { setImage(44); }
  AT(0,1,58.110)   { setImage(45); }
  AT(0,2,01.260)   { setImage(46); }
  
  AT(0,2,13.320)   { setImage(47); }
  AT(0,2,25.390)   { setImage(48); }
  AT(0,2,31.370)   { setImage(49); }
  AT(0,2,37.350)   { setImage(48); }
  AT(0,2,40.440)   { setImage(56); } // Buzz comet

  AT(0,2,46.240)   { setImage(61); }
  AT(0,2,50.260)   { setImage(62); }
  AT(0,2,54.140)   { setImage(59); }
  AT(0,2,58.060)   { setImage(46); }
  AT(0,3,05.370)   { setImage(47); }
  AT(0,3,13.230)   { setImage(56); }
  AT(0,3,17.330)   { setImage(61); }
  AT(0,3,21.210)   { setImage(62); }
  AT(0,3,25.100)   { setImage(59); }
  AT(0,3,29.000)   { setImage(46); }
  AT(0,3,36.340)   { setImage(47); }
  AT(0,3,43.130)   { setImage(57); }

  AT(0,3,49.000)   { setImage(0); }
} 





void RestartPerformance() {
  gLastTimeCodeDoneAt   = 0;
  gLastTimeCodeDoneFrom = 0;
  gTimeCodeBase         = millis();
}


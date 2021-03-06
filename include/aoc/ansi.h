#ifndef AOC_ANSI_H
#define AOC_ANSI_H

#define ANSI_ESCAPE(str) "\x1b[" str

#define ANSI_RESET ANSI_ESCAPE("0m")
#define ANSI_BOLD_ON ANSI_ESCAPE("1m")
#define ANSI_BOLD_OFF ANSI_ESCAPE("22m")
#define ANSI_FAINT_ON ANSI_ESCAPE("2m")
#define ANSI_FAINT_OFF ANSI_ESCAPE("22m") // same as ANSI_BOLD_OFF
#define ANSI_ITALIC_ON ANSI_ESCAPE("3m")
#define ANSI_ITALIC_OFF ANSI_ESCAPE("23m")
#define ANSI_UNDERSCORE_ON ANSI_ESCAPE("4m")
#define ANSI_UNDERSCORE_OFF ANSI_ESCAPE("24m")
#define ANSI_BLINK_ON ANSI_ESCAPE("5m")
#define ANSI_BLINK_OFF ANSI_ESCAPE("25m")
#define ANSI_INVERT_ON ANSI_ESCAPE("7m")
#define ANSI_INVERT_OFF ANSI_ESCAPE("27m")
#define ANSI_CROSSED_OUT_ON ANSI_ESCAPE("9m")
#define ANSI_CROSSED_OUT_OFF ANSI_ESCAPE("29m")

#define ANSI_FG_DEFAULT ANSI_ESCAPE("39m")

#define ANSI_FG_BLACK ANSI_ESCAPE("30m")
#define ANSI_FG_RED ANSI_ESCAPE("31m")
#define ANSI_FG_GREEN ANSI_ESCAPE("32m")
#define ANSI_FG_YELLOW ANSI_ESCAPE("33m")
#define ANSI_FG_BLUE ANSI_ESCAPE("34m")
#define ANSI_FG_MAGENTA ANSI_ESCAPE("35m")
#define ANSI_FG_CYAN ANSI_ESCAPE("36m")
#define ANSI_FG_WHITE ANSI_ESCAPE("37m")

#define ANSI_FG_LIGHT_BLACK ANSI_ESCAPE("90m")
#define ANSI_FG_LIGHT_RED ANSI_ESCAPE("91m")
#define ANSI_FG_LIGHT_GREEN ANSI_ESCAPE("92m")
#define ANSI_FG_LIGHT_YELLOW ANSI_ESCAPE("93m")
#define ANSI_FG_LIGHT_BLUE ANSI_ESCAPE("94m")
#define ANSI_FG_LIGHT_MAGENTA ANSI_ESCAPE("95m")
#define ANSI_FG_LIGHT_CYAN ANSI_ESCAPE("96m")
#define ANSI_FG_LIGHT_WHITE ANSI_ESCAPE("97m")

#define ANSI_FG_8BIT(color) ANSI_ESCAPE("38;5;" color "m")
#define ANSI_FG_24BIT(color) ANSI_ESCAPE("38;2;" color "m")

#define ANSI_BG_DEFAULT ANSI_ESCAPE("49m")

#define ANSI_BG_BLACK ANSI_ESCAPE("40m")
#define ANSI_BG_RED ANSI_ESCAPE("41m")
#define ANSI_BG_GREEN ANSI_ESCAPE("42m")
#define ANSI_BG_YELLOW ANSI_ESCAPE("43m")
#define ANSI_BG_BLUE ANSI_ESCAPE("44m")
#define ANSI_BG_MAGENTA ANSI_ESCAPE("45m")
#define ANSI_BG_CYAN ANSI_ESCAPE("46m")
#define ANSI_BG_WHITE ANSI_ESCAPE("47m")

#define ANSI_BG_LIGHT_BLACK ANSI_ESCAPE("100m")
#define ANSI_BG_LIGHT_RED ANSI_ESCAPE("101m")
#define ANSI_BG_LIGHT_GREEN ANSI_ESCAPE("102m")
#define ANSI_BG_LIGHT_YELLOW ANSI_ESCAPE("103m")
#define ANSI_BG_LIGHT_BLUE ANSI_ESCAPE("104m")
#define ANSI_BG_LIGHT_MAGENTA ANSI_ESCAPE("105m")
#define ANSI_BG_LIGHT_CYAN ANSI_ESCAPE("106m")
#define ANSI_BG_LIGHT_WHITE ANSI_ESCAPE("107m")

#define ANSI_BG_8BIT(color) ANSI_ESCAPE("48;5;" color "m")
#define ANSI_BG_24BIT(color) ANSI_ESCAPE("48;2;" color "m")

#endif // AOC_ANSI_H

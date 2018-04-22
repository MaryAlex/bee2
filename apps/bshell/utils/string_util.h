//
// Created by Maria Chmyreva on 3/10/18.
//

#ifndef BSHELL_INPUT_CONVERTER_H
#define BSHELL_INPUT_CONVERTER_H

/***
 * @param input arguments from console
 * @return command that was entered after --
 */
char *get_command_name(char **);

/***
 * @return argument that comes after argument_name
 */
char *get_optional_argument_value(int argc, char **argv, const char *argument_name);
char *get_required_argument_value(int argc, char **argv, const char *argument_name);

#endif //BSHELL_INPUT_CONVERTER_H

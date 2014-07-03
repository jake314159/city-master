
#
# Usage:
#    bash addString NAME_OF_MY_STRING "My string"
#
# Where NAME_OF_MY_STRING is in all caps and _ only

# Write the text into a file with the correct name with an extra null
# character on the end
echo -en "$2\0" > game_resources/strings/$1


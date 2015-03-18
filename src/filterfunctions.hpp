#ifndef FILTERFUNCTIONS_H
#define FILTERFUNCTIONS_H

class Map;

void islandizeFilter(const Map *input, Map *output);
void flattenFilter(const Map *input, Map *output);
void smoothFilter(const Map *input, Map *output);
void colorizeFilter(const Map *input, Map *output);

#endif // FILTERFUNCTIONS_H

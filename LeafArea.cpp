#include "includes/LeafArea.h"

LeafArea::LeafArea()
{}

LeafArea::LeafArea(OCTET* data, int w , int h , int x , int y) : AbstractArea(data , w , h , x , y )
{

}

LeafArea::~LeafArea() //TODO
{

}

void LeafArea::split(int seuil)
{

}
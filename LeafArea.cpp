#include "includes/LeafArea.h"

LeafArea::LeafArea()
{}

LeafArea::LeafArea(int w , int h , int x , int y) : AbstractArea( w , h , x , y )
{

}

LeafArea::LeafArea(OCTET* data, int w , int h , int x , int y) : AbstractArea(data , w , h , x , y )
{

}

LeafArea::~LeafArea() //TODO
{

}

LeafArea::split(seuil)
{

}
//-*- mode: c++ -*-////////////////////////////////////////////////////////////
//                       Copyright (c) 2011 - 2012 by                        //
//                                Simon Pratt                                //
//                           (All rights reserved)                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// FILE:    PointPersistentList.h                                            //
//                                                                           //
// MODULE:  Persistent List                                                  //
//                                                                           //
// PURPOSE: Uses a persistent list to store points and perform queries.      //
//                                                                           //
// NOTES:   None.                                                            //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Public Variable:                     Description:                         //
// ----------------                     ------------                         //
// coord_t Point2d.x                    the x coordinate of a point          //
// coord_t Point2d.y                    the y coordinate of a point          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             Public Methods:                               //
//                                                                           //
// Point2d::Point2d(coord_t x, coord_t y)                                    //
// ostream& operator<<(ostream& os, const Point2d& p)                        //
//                                                                           //
// PersistentList::PointPersistentList()                                     //
// int PersistentList::insertPoint(coord_t x, coord_t y)                     //
// vector<Point2d> PersistentList::enumerateNE(coord_t x, coord_t y)         //
// Point2d* PersistentList::highestNE(coord_t x, coord_t y)                  //
// ListNode<Point2d>* PersistentList::getList(int t)                         //
// void PersistentList::printArray()                                         //
// size_t PersistentList::size()                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef POINTPERSISTENTLIST_H
#define POINTPERSISTENTLIST_H

#include <vector>
#include "PersistentList.h"

namespace persistent_list {
  // Defines the implementation and precision of coordinates
  typedef int coord_t;
  
  /////////////////////////////////////////////////////////////////////////////
  // Point2d interface                                                       //
  /////////////////////////////////////////////////////////////////////////////
  class Point2d {
  public:
    coord_t x, y;

    ///////////////////////////////////////////////////////////////////////////
    //                                                                       //
    // FUNCTION NAME: Point2d                                                //
    //                                                                       //
    // PURPOSE:       Basic constructor.                                     //
    //                                                                       //
    // SECURITY:      public                                                 //
    //                                                                       //
    // PARAMETERS                                                            //
    //   Type/Name:   coord_t/x                                              //
    //   Description: The x coordinate of a point in 2d.                     //
    //                                                                       //
    //   Type/Name:   coord_t/y                                              //
    //   Description: The y coordinate of a point in 2d.                     //
    //                                                                       //
    // NOTES:         None.                                                  //
    //                                                                       //
    ///////////////////////////////////////////////////////////////////////////
    Point2d(coord_t x, coord_t y)
      : x(x), y(y)
    {}
  };

  /////////////////////////////////////////////////////////////////////////////
  //                                                                         //
  // FUNCTION NAME: operator<<                                               //
  //                                                                         //
  // PURPOSE:       Formats a Point2d nicely for an ostream.                 //
  //                                                                         //
  // SECURITY:      public                                                   //
  //                                                                         //
  // PARAMETERS                                                              //
  //   Type/Name:   ostream/os                                               //
  //   Description: An os to which to send the Point2d.                      //
  //                                                                         //
  //   Type/Name:   Point2d/p                                                //
  //   Description: The Point2d to format and send.                          //
  //                                                                         //
  // RETURN:        The ostream input.                                       //
  //                This is standard practice for chaining such as:          //
  //                cout << "Point: " << point << endl;                      //
  //                                                                         //
  // NOTES:         None.                                                    //
  //                                                                         //
  /////////////////////////////////////////////////////////////////////////////
  ostream& operator<<(ostream& os, const Point2d& p);
  
  /////////////////////////////////////////////////////////////////////////////
  // PointPersistentList interface                                           //
  /////////////////////////////////////////////////////////////////////////////
  class PointPersistentList {
    // An array of points sorted by x coordinate
    vector<Point2d> points_sorted_by_x;

    // A persistent list of points sorted by y coordinate
    PersistentList< Point2d > points_right;

    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: binarySearchX                                            //
    //                                                                         //
    // PURPOSE:       determines the position of a 2d point in the sorted      //
    //                array.  If the point is not in the array, this           //
    //                method will return the index of where the element        //
    //                should be in the array.                                  //
    //                                                                         //
    // SECURITY:      private                                                  //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   coord_t/x                                                //
    //   Description: The x coordinate for which to search.                    //
    //                                                                         //
    // RETURN:        The index of the x coordinate in the array, or the       //
    //                index where the x coordinate should be.                  //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    int binarySearchX(coord_t x);

    ///////////////////////////////////////////////////////////////////////////
    //                                                                       //
    // FUNCTION NAME: getNodeBefore                                          //
    //                                                                       //
    // PURPOSE:       Returns the node directly preceding a node with        //
    //                a given y-coordinate, or where that node should be.    //
    //                                                                       //
    // SECURITY:      private                                                //
    //                                                                       //
    // PARAMETERS                                                            //
    //   Type/Name:   int/t                                                  //
    //   Description: The list time (version) to search                      //
    //                                                                       //
    //   Type/Name:   coord_t/y                                              //
    //   Description: The y-coordinate for which to search                   //
    //                                                                       //
    // RETURN:                                                               //
    //   Type/Name:   ListNode<Point2d>*                                     //
    //   Description: The node preceding or which would precede a node       //
    //                with the given y coordinate.                           //
    //                                                                       //
    // NOTES:         None.                                                  //
    //                                                                       //
    ///////////////////////////////////////////////////////////////////////////
    ListNode<Point2d>* getNodeBefore(int t, coord_t y);
    
  public:
    ///////////////////////////////////////////////////////////////////////////
    //                                                                       //
    // FUNCTION NAME: PointPersistentList                                    //
    //                                                                       //
    // PURPOSE:       Empty constructor.                                     //
    //                                                                       //
    // SECURITY:      public                                                 //
    //                                                                       //
    // PARAMETERS                                                            //
    //   Type/Name:   Void.                                                  //
    //   Description: None.                                                  //
    //                                                                       //
    // NOTES:         None.                                                  //
    //                                                                       //
    ///////////////////////////////////////////////////////////////////////////
    PointPersistentList()
      : points_sorted_by_x(), points_right()
    {}

    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: insertPoint                                              //
    //                                                                         //
    // PURPOSE:       Inserts a point into the structure, with given x and y   //
    //                coordinates.                                             //
    //                                                                         //
    // SECURITY:      public                                                   //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   coord_t/x                                                //
    //   Description: x-coordinate                                             //
    //                                                                         //
    //   Type/Name:   coord_t/y                                                //
    //   Description: y-coordinate                                             //
    //                                                                         //
    // RETURN:                                                                 //
    //   Type/Name:   int                                                      //
    //   Description: 0 for success.                                           //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    int insertPoint(coord_t x,coord_t y);

    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: enumerateNE                                              //
    //                                                                         //
    // PURPOSE:       Returns the a vector of all points where the             //
    //                x-coordinate is greater than or equal to the given       //
    //                x, and the y-coordinate is greater than or equal         //
    //                to the given y.                                          //
    //                                                                         //
    // SECURITY:      public                                                   //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   coord_t/x                                                //
    //   Description: The minimum x coordinate to consider.                    //
    //                                                                         //
    //   Type/Name:   coord_t/y                                                //
    //   Description: The minimum y coordinate to consider.                    //
    //                                                                         //
    // RETURN:        A vector of all points p s.t. p.x >= x, p.y >= y.        //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    vector< Point2d > enumerateNE(coord_t x, coord_t y);
    
    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: highestNE                                                //
    //                                                                         //
    // PURPOSE:       Returns the highest point in the set of all points       //
    //                where the x-coordinate is greater than or equal to       //
    //                the given x, and the y-coordinate is greater than        //
    //                or equal to the given y.                                 //
    //                                                                         //
    // SECURITY:      public                                                   //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   coord_t/x                                                //
    //   Description: The minimum x coordinate to consider.                    //
    //                                                                         //
    //   Type/Name:   coord_t/y                                                //
    //   Description: The minimum y coordinate to consider.                    //
    //                                                                         //
    // RETURN:        The highest point p where p.x >= x, p.y >= y.            //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    Point2d* highestNE(coord_t x, coord_t y);

    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: getList                                                  //
    //                                                                         //
    // PURPOSE:       Returns the list of points at time t.                    //
    //                                                                         //
    // SECURITY:      public                                                   //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   int/t                                                    //
    //   Description: The time (version) of the list structure.                //
    //                                                                         //
    // RETURN:                                                                 //
    //   Type/Name:   ListNode<Point2d>                                        //
    //   Description: The list at time t.                                      //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    ListNode<Point2d>* getList(int t);
    
    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: printArray                                               //
    //                                                                         //
    // PURPOSE:       Prints the points sorted by x to cout.                   //
    //                                                                         //
    // SECURITY:      public                                                   //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   Void.                                                    //
    //   Description: None.                                                    //
    //                                                                         //
    // RETURN:        Void.                                                    //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    void printArray();

    /////////////////////////////////////////////////////////////////////////////
    //                                                                         //
    // FUNCTION NAME: size                                                     //
    //                                                                         //
    // PURPOSE:       Returns the number of points in the structure.           //
    //                                                                         //
    // SECURITY:      public                                                   //
    //                                                                         //
    // PARAMETERS                                                              //
    //   Type/Name:   Void.                                                    //
    //   Description: None.                                                    //
    //                                                                         //
    // RETURN:        size_t number of points in the structure.                //
    //                                                                         //
    // NOTES:         None.                                                    //
    //                                                                         //
    /////////////////////////////////////////////////////////////////////////////
    size_t size();
  };
}

#endif

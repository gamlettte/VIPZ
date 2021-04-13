#include <stdio.h>
#include <stdlib.h>
#define MARKS_NUMBER 4

struct Date
{
    short unsigned Day ;
    short unsigned Month ;
    short unsigned Year ;
};
typedef struct Student
{
    char has_five ;
    struct Date BirthDate ;
    double AverageMark ;
    struct Student* next ;
    char Name [16] ;
    char Surname [16] ;
    short Marks [MARKS_NUMBER] ;
}node;
void Calculate_average_mark ( node* pStud )
{
    double sum = 0 ;
    for ( int i = 0 ; i < MARKS_NUMBER ; i ++ )
    {
        sum +=pStud->Marks[i] ;
    }
    pStud->AverageMark = sum / MARKS_NUMBER ;
}
void Print_student ( node* pStud )
{
    printf ( "%-15s %-16s | %2d.%2d.%4d |" ,
            pStud->Name,
            pStud->Surname,
            pStud->BirthDate.Day,
            pStud->BirthDate.Month,
            pStud->BirthDate.Year ) ;
    for ( int j = 0 ; j < MARKS_NUMBER ; j ++ )
    {
        printf ( "|%d|", pStud->Marks[j] ) ;
    }   printf ( "\n" ) ;
}
void Scan_students_from_file ( FILE* source, node** StudList )
{
    while ( ! feof ( source ) )
    {
        node* p = NULL ;
        p = (node*)malloc(sizeof(node));
        fscanf ( source , "%d.%d.%d %s %s",
                &(p->BirthDate.Day),
                &(p->BirthDate.Month),
                &(p->BirthDate.Year),
                &(p->Name),
                &(p->Surname) ) ;
                p->has_five = 0 ;
        for ( int j = 0 ; j < MARKS_NUMBER ; j ++ )
        {
            fscanf( source , "%d", &(p->Marks[j]) );
            if ( p->Marks[j] == 5 )
                p->has_five = 1 ;
        }
        Calculate_average_mark ( p ) ;
        p->next = *StudList ;
        *StudList = p ;
    }
    fclose ( source ) ;
}

/*void Get_students_from_user (node** Studlist )
{
    printf ( "write by enter the name, surname, day, month and year of birth and set of four marks by space") ;
    node* temp ;
    while ( scanf ( "%s") != 2 )
    {

    }
}
*/
void Delete_first_node (node** list)
{
    node* temp = *list ;
    *list = temp->next ;
    free ( temp ) ;
}
void Delete_by_trait ( node** StudList )
{
    node* temp = *StudList;
    if ( temp->Marks[0] == 3 && temp->Marks[2] == 3 )
    {
        Delete_first_node ( StudList ) ;
    }
    node* prev = NULL ;
    while ( temp->next )
    {
        prev = temp ;
        temp = temp->next ;
        if ( temp->Marks[0] == 3 && temp->Marks[2] == 3 )
        {
            prev->next = temp->next ;
            free (temp) ;
            temp = prev ;
        }
    }
}
node * Release_first_node ( node** List )
{
    struct Student* temp = *List ;
    *List = temp->next ;
    return temp ;
}
void Paste_node_by_field ( node** List, node* node1, int (*is_first_less)(node*, node*))
{
    struct Student* temp = *List ;
    while (!(is_first_less (temp->next, node1 ) ) && temp )
    {
        temp = temp->next ;
    }
    node1->next = temp->next ;
    temp->next = node1 ;
}
void Sort_by_field ( node** StudList, int (*is_first_less)(node*, node* ) )
{
    for ( int i = 0 ; i < length_of_list ( *StudList ) ; i++ )
    {
        node* temp = (*StudList)->next, * prev = *StudList ;
        while ( temp->next )
        {
            if ( is_first_less ( temp, temp->next ) )
            {
                prev->next = temp->next ;
                temp->next = temp->next->next ;
                prev->next->next = temp ;
                prev = prev->next ;
            }
            else {
                prev = temp ;
                temp = temp->next ;
            }
        }
    }
    Print_list (*StudList) ;
    printf ( "\n\n") ;
    Paste_node_by_field ( StudList, Release_first_node (StudList), is_first_less ) ;
}
void Print_list ( node* head )
{
    node* helper = head ;
    while ( helper )
    {
        Print_student ( helper ) ;
        helper = helper->next ;
    }
    printf ( "\n" ) ;
}
int Is_second_elder ( node* a, node* b )
{
    if ( a->BirthDate.Year < b->BirthDate.Year )   return 1 ;
    else
    if ( a->BirthDate.Year > b->BirthDate.Year )   return 0 ;
    else
    if ( a->BirthDate.Month < b->BirthDate.Month ) return 1 ;
    else
    if ( a->BirthDate.Month > b->BirthDate.Month ) return 0 ;
    else
    if ( a->BirthDate.Day < b->BirthDate.Day )     return 1 ;
    else
    if ( a->BirthDate.Day >= b->BirthDate.Day )    return 0 ;
}
int length_of_list ( node* list)
{
    int count = 0 ;
    while ( list )
    {
        list = list->next ;
        count ++ ;
    }
    return count ;
}
int main()
{
    FILE* source = fopen ( "students.txt", "r" ) ;
    node* StudList = NULL;
    Scan_students_from_file ( source, &StudList ) ;
    Print_list ( StudList ) ;
    Delete_by_trait( &StudList ) ;
    Print_list ( StudList ) ;
    Sort_by_field ( &StudList, &Is_second_elder ) ;
    Print_list ( StudList ) ;
    return 0;
}


#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p4.h"

/****************************removeLL******************************************
 * int removeLL(LinkedList list, Event *pValue)
 * Purpose:
 *      This function returns false if the list is empty otherwise it returns 
 *      true and removes the first node in the list.
 * Parameters:
 *      O Linkedlist list         list containing all the event nodes
 *      O Event *pValue           pointer to the node event being removed
 * Notes:
 * 
 * Returns:
 *      TRUE                      list contained nodes and head was removed
 *      FALSE                     list was empty 
 * ****************************************************************************/

int removeLL(LinkedList list, Event *pValue)
{
    NodeLL *pRemove;
    //check to see if list is empty
    if(list->pHead == NULL)
        return FALSE;
    //return the element value via piValue
    *pValue = list->pHead->event;
    
    //set pRemove to point to the node being removed and remove it
    pRemove = list->pHead;
    list->pHead = list->pHead->pNext;
    free(pRemove);
    return TRUE;

    
}

/****************************insertOrderedLL***********************************
 * NodeLL *insertLL(LinkedList list, Event Value)
 * Purpose:
 *      This function inserts a node to a linked list. if uses to searchLL to 
 *      know where to insert.
 * Parameters:
 *      O Linkedlist list         list containing all the event nodes
 *      I Event value             event structure to be inserted
 * Notes:
 * 
 * Returns:
 *      pNew                      The node inserted correctly in the linked list
 * ****************************************************************************/
NodeLL *insertOrderedLL(LinkedList list, Event value)
{
    NodeLL *pNew, *pFind, *pPrecedes;
    //see if it already exists
    //Notice that we are passing the address of pPrecedes so that
    //searchLL can change it.
    pFind = searchLL(list, value.iTime, &pPrecedes);
    
    pNew = allocNodeLL(list, value);
    
    if(pPrecedes == NULL)
    {
        pNew->pNext = list->pHead;
        list->pHead = pNew;
    }
    else
    {
        pNew->pNext = pPrecedes->pNext;
        pPrecedes->pNext = pNew;
    }
    return pNew;
    
}

/****************************searchLL******************************************
 * NodeLL *searchLL(LinkedList list, int match, NodeLL **ppPrecedes)
 * Purpose:
 *      This function searches the list for a match. It also returns through 
 *      parameter the preceding node.
 * Parameters:
 *      I Linkedlist list         list containing all the event nodes
 *      I int match               event time value to be compared
 *      O NodeLL **ppPrecedes     the preceding node
 * Notes:
 * 
 * Returns:
 *      p                      The node if it already exists
 *      NULL                   The node doesn't exist
 * ****************************************************************************/
NodeLL *searchLL(LinkedList list, int match, NodeLL **ppPrecedes)
{ 
    NodeLL *p;
    //NULL used when the list is empty
    //or when we need to insert at the beginning 
    *ppPrecedes = NULL;
    
    //Tranverse through the list looking for a match
    for(p = list->pHead; p!=NULL; p = p->pNext)
    {
        if(match == p->event.iTime)
            return p;
        if(match < p->event.iTime)
            return NULL;
        *ppPrecedes = p;
    }
    return NULL;
    
    
    
    
}

/****************************newLinkedList*************************************
 * LinkedList newLinkedList()
 * Purpose:
 *      This function creates and returns a list and sets it to null
 * Parameters:
 *    
 * Notes:
 * 
 * Returns:
 *     list                     The list created
 * ****************************************************************************/
LinkedList newLinkedList()
{
    LinkedList list = (LinkedList) malloc(sizeof(LinkedListImp));
    if (list == NULL)
        errExit("could not allocate LinkedList");
     
    
    //Mark the list as empty
    list->pHead = NULL;
    return list;
    
    
}

/****************************allocNodeLL***********************************
 * NodeLL *insertLL(LinkedList list, Event Value)
 * Purpose:
 *      This function allocates a node and points its next to NULL.
 * Parameters:
 *      I Linkedlist list         list containing all the event nodes
 *      I Event value             event structure to be allocated
 * Notes:
 * 
 * Returns:
 *      pNew                      The node allocated correctly in the linked list
 * ****************************************************************************/
NodeLL *allocNodeLL(LinkedList list, Event value)
{
    NodeLL *pNew;
    pNew = (NodeLL *)malloc(sizeof(NodeLL));
    if(pNew == NULL)
        errExit("Could not allocate NodeLL");
    pNew->event = value;
    pNew->pNext = NULL;
    
    return pNew;
    
    
    
}

/*********************************removeQ****************************************
 int removeQ(Queue queue, QElement *pFromQElement)
 * Purpose:
 *       Removes a node from the head of the queue and returns its value through parameter
 * Parameters
 *      I Queue queue               Where node is removed from
 *      O QElement *pFromQElement   Pointer to what was removed
 * 
 * Return:
 *      1                           If the list isn't empty
 *      0                           If the list is empty 
 
 
*******************************************************************************/
int removeQ(Queue queue, QElement *pFromQElement)
{
    NodeQ *pRemove;
    if(queue->pHead == NULL)
        return FALSE;
    pRemove = queue->pHead;
    *pFromQElement = pRemove->element;
    queue->pHead = pRemove->pNext;
    if(queue->pFoot == pRemove)
        queue->pFoot = NULL;
    free(pRemove);
    return TRUE;
    
}

/*****************************************************************************
 void insertQ(Queue queue, QElement element)
 * Purpose:
 *       inserts a node to the foot of the queue
 * Parameters
 *      I Queue queue               Where node is inserted in
 *      O QElement element          the element value contained in the node
 * 
 * Return:
 *    None 
 ******************************************************************************/
void  insertQ(Queue queue, QElement element)
{
   NodeQ *pNew;
   pNew = allocNodeQ(queue, element);
   if(pNew == NULL)
       errExit("could not allocate NodeQ");
   //check for empty
   if(queue->pFoot == NULL)
   {
       queue->pFoot = pNew;
       queue->pHead=pNew;
       
   }
   else
   {
       queue->pFoot->pNext = pNew;
       queue->pFoot = pNew;
   }
}



/*****************************************************************************
 NodeQ *allocNodeQ(Queue queue, QElement value)
 * Purpose:
 *       allocates memory for a new node and sets its next to null
 * Parameters
 *      I Queue queue               Where node is inserted in
 *      O QElement element          the element value contained in the node
 * 
 * Return:
 *    The new node allocated
 
 ******************************************************************************/
NodeQ *allocNodeQ(Queue queue, QElement value)
{
    NodeQ *pNew;
    pNew = (NodeQ *)malloc(sizeof(NodeQ));
    if(pNew == NULL)
        errExit("Could not allocate NOdeQ");
    pNew->element = value;
    pNew->pNext = NULL;
    return pNew;
    
    
}

/******************************************************************************
 Queue newQueue(char szQueueNm[])
 * Purpose:
 *      creates a new queue
 * Parameter:
 *      I char szQueueNm[]            The name of the queue
 * Return:
 *      the new queue with head and foot pointing to null.
 * 
 ******************************************************************************/
Queue newQueue(char szQueueNm[])
{
    Queue queue = (Queue)malloc(sizeof(QueueImp));
    if(queue == NULL)
        errExit("could not allocate Queue");
    queue->pHead = NULL;
    queue->pFoot = NULL;
    queue->lQueueWaitSum = 0;
    queue->lQueueWidgetTotalCount = 0;
    strcpy(queue->szQName, szQueueNm);
    return queue;
}

/****************************newSimulation**************************************
 * Simulation newSimulation()
 * Purpose:
 *      This function creates a new simulation and creates an event linked list
 *      for the simulation.
 * Parameters:
 *  
 * Notes:
 * 
 * Returns:
 *      simulation                        new simulation created
 *      
 * ****************************************************************************/

Simulation newSimulation()
{
    Simulation simulation = (Simulation)malloc(sizeof(SimulationImp));
    if (simulation == NULL)
        errExit("Could not allocate simulation");
    simulation->iClock = 0;
    simulation->eventList = newLinkedList();
    simulation->lWidgetCount = 0;
    simulation->lSystemTimeSum  = 0;
    return simulation;
    
    
}

/****************************readsInput**************************************
 * void readsInput(Simulation simulation)
 * Purpose:
 *      This function stores the person, departure times, and arrival time in nodes
 *      in the  simulation event list.
 * Parameters:
 *     I/O Simulation simulation         simulation passed in with the event list
 * Notes:
 * 
 * Returns:
 *      
 * ****************************************************************************/
void readsInput (Simulation simulation)
{
   
    char szInputBuffer[MAX_LINE_SIZE];  // input buffer for fgets
    int iScanfCnt;
    int iTime = 0;
    
    while (fgets(szInputBuffer, MAX_LINE_SIZE, stdin) != NULL)
    {
        Widget widget;
        Event eventArrive;
        int iDeltaNextArrival;
        // if just a line feed, skip it.
        if (szInputBuffer[0] == '\n')
            continue;
        iScanfCnt  = sscanf(szInputBuffer, "%ld %d %d %d %d" , &widget.lWidgetNr
                ,&widget.iStep1tu
                ,&widget.iStep2tu
                ,&iDeltaNextArrival
                ,&widget.iWhichServer);
        if(iScanfCnt < 5)
            errExit("\tWarning: read only %d successful values ", iScanfCnt); 
        
        eventArrive.iTime = iTime;
        eventArrive.widget = widget;
        eventArrive.iEventType = EVT_ARRIVAL;
        
        insertOrderedLL(simulation->eventList, eventArrive);
        
        iTime = iTime + iDeltaNextArrival;
        
        
      
    }
}
/******************** errExit **************************************
    void errExit(char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
    It also exits the program, returning ERR_EXIT.
Parameters:
    I   char szFmt[]            This contains the message to be printed
                                and format codes (just like printf) for 
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt. 
Returns:
    Returns a program exit return code:  the value of ERR_EXIT.
Notes:
    - Prints "ERROR: " followed by the formatted error message specified 
      in szFmt. 
    - Prints the file path and file name of the program having the error.
      This is the file that contains this routine.
    - Requires including <stdarg.h>
**************************************************************************/
void errExit(char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n\tEncountered in file %s\n", __FILE__);  // this 2nd arg is filled in by
                                // the pre-compiler
    exit(ERR_EXIT);
}

/**************************newServer***********************************************
 *       Server newServer(char szServerName[])
 * * Purpose:
 *      creates a new server
 * Parameter:
 *      I char szServerName[]            The name of the server
 * Return:
 *      the new server created and set to not busy.
 * 
 *****************************************************************************/
Server newServer(char szServerName[])
{
    Server server= (Server) malloc(sizeof(ServerImp));
    if (server == NULL)
        errExit("could not allocate server");
    strcpy(server->szServerName, szServerName);
    server->bBusy = FALSE;
    return server;
    
}

/*************************arrival**********************************************
 *       void arrival (Simulation simulation, Widget *widget)
 * * Purpose:
 *      sets the arrival time for a widget.
 * Parameter:
 *      I Simulation simulation       The simulation passed in
 *      I Widget *widget               The widget current
 * Return:
 *      
 * 
 *****************************************************************************/
void arrival(Simulation simulation, Widget *widget)
{
    widget->iArrivalTime = simulation->iClock;
    if(simulation->bVerbose == TRUE)
        printf("%4d    %2ld     Arrived\n", widget->iArrivalTime, widget->lWidgetNr);
    
}

/************************queueUp*********************************************
 *       void queueUp (Simulation simulation, Queue queue, Widget *widget)
 * * Purpose:
 *      inserts a widget in the queue and set the arrival time.
 * Parameter:
 *      I Simulation simulation        The simulation passed in
 *      I Queue queue                  The queue the widget gets inserted 
 *      I Widget *widget               The widget current
 * Return:
 *      
 * 
 *****************************************************************************/
void queueUp(Simulation simulation, Queue queue, Widget *widget)
{
    QElement element;
    element.widget = *widget;
    element.iEnterQTime = simulation->iClock; 
    if(simulation->bVerbose == TRUE)
        printf("%4d    %2ld     Enter Queue %s\n", element.iEnterQTime, widget->lWidgetNr, queue->szQName);
    queue->lQueueWidgetTotalCount = queue->lQueueWidgetTotalCount +1;
    insertQ(queue,element);
    
    
    
}
/*****************************seize********************************************
 *       void seize (Simulation simulation, Queue queue, Server server)
 * * Purpose:
 *      seizes a server if it's not busy and calculate the time widget is in server
 * Parameter:
 *      I Simulation simulation        The simulation passed in
 *      I Queue queue                  The queue passed in 
 *      I server server                The server being used
 * Return:
 *      
 * 
 *****************************************************************************/
void seize(Simulation simulation, Queue queue, Server server)
{
    QElement pFromQElement;
    Event eventSeize;
    int WidgetWaitSum;
    if(server->bBusy == FALSE && removeQ(queue, &pFromQElement))
    {
       server->bBusy = TRUE;
       
       server->widget = pFromQElement.widget;
       WidgetWaitSum =simulation->iClock - pFromQElement.iEnterQTime;
       queue->lQueueWaitSum += WidgetWaitSum;
       
       eventSeize.iTime  = simulation->iClock + server->widget.iStep1tu + server->widget.iStep2tu;
       
       if(strcmp(server->szServerName, "W")==0)
          eventSeize.iEventType = EVT_SERVERW_COMPLETE;
       else if (strcmp(server->szServerName, "M")== 0)
           eventSeize.iEventType = EVT_SERVERM_COMPLETE;
       
       eventSeize.widget = server->widget;  
       
       if(simulation->bVerbose == TRUE)
       {
            printf("%4d    %2ld     Leave Queue %s  Waited %d\n",  simulation->iClock, eventSeize.widget.lWidgetNr
            ,queue->szQName
            ,WidgetWaitSum);
            printf("%4d    %2ld     Seized Server %s \n", simulation->iClock, eventSeize.widget.lWidgetNr, server->szServerName);
       }
       insertOrderedLL(simulation->eventList, eventSeize);
    }
}
/*****************************seizeAlternativeB********************************************
 *       void seizeAlternativeB (Simulation simulation, Queue queue, Server server)
 * * Purpose:
 *      seizes a server if it's not busy and calculate the time widget is in server
 * Parameter:
 *      I Simulation simulation        The simulation passed in
 *      I Queue queue                  The queue passed in 
 *      I server server                The server being used
 * Return:
 *      
 * 
 *****************************************************************************/
void seizeAlternativeB(Simulation simulation, Queue queue, Server server)
{
    QElement pFromQElement;
    Event eventComplete;
    int WidgetWaitSum;
    if(server->bBusy == FALSE && removeQ(queue, &pFromQElement))
    {
       server->bBusy = TRUE;
       
       server->widget = pFromQElement.widget;
       WidgetWaitSum =simulation->iClock - pFromQElement.iEnterQTime;
       queue->lQueueWaitSum += WidgetWaitSum;
       if(strcmp(server->szServerName, "W")==0){
            eventComplete.iTime  = simulation->iClock + server->widget.iStep1tu;
            eventComplete.iEventType = EVT_SERVERW_COMPLETE;
       }
       if(strcmp(server->szServerName, "X")==0 ) {
            eventComplete.iTime  = simulation->iClock + server->widget.iStep2tu;
            eventComplete.iEventType = EVT_SERVERX_COMPLETE;
       }
       if (strcmp(server->szServerName, "Y")== 0){
            eventComplete.iTime  = simulation->iClock + server->widget.iStep2tu;
            eventComplete.iEventType = EVT_SERVERY_COMPLETE;
       }
           
       
       eventComplete.widget = server->widget;  
       
       if(simulation->bVerbose == TRUE)
       {
            printf("%4d    %2ld     Leave Queue %s  Waited %d\n",  simulation->iClock, eventComplete.widget.lWidgetNr
            ,queue->szQName
            ,WidgetWaitSum);
            printf("%4d    %2ld     Seized Server %s \n", simulation->iClock, eventComplete.widget.lWidgetNr, server->szServerName);
       }
       insertOrderedLL(simulation->eventList, eventComplete);
    }
}

/**************************releaseAlternativeB**********************************************
 *       void releaseAlternativeB (Simulation simulation, Queue queue, Server server, Widget *widget)
 * * Purpose:
 *      releases a server after widget is finished
 * Parameter:
 *      I Simulation simulation        The simulation passed in
 *      I Queue queue                  The queue passed in 
 *      I Server server                The server being used
 *      I Widget *widget               The widget current
 * Return:
 *      
 * 
 ***************************************************************************/
    
void releaseAlternativeB(Simulation simulation, Queue queue, Server server, Widget *widget)
{
    server->bBusy = FALSE;
    if(simulation->bVerbose == TRUE)
        printf("%4d    %2ld     Released Server %s\n", simulation->iClock, widget->lWidgetNr, server->szServerName);
    seizeAlternativeB(simulation, queue, server);
    
}
/**************************release**********************************************
 *       void release (Simulation simulation, Queue queue, Server server, Widget *widget)
 * * Purpose:
 *      releases a server after widget is finished
 * Parameter:
 *      I Simulation simulation        The simulation passed in
 *      I Queue queue                  The queue passed in 
 *      I Server server                The server being used
 *      I Widget *widget               The widget current
 * Return:
 *      
 * 
 ***************************************************************************/
    
void release(Simulation simulation, Queue queue, Server server, Widget *widget)
{
    server->bBusy = FALSE;
    if(simulation->bVerbose == TRUE)
        printf("%4d    %2ld     Released Server %s\n", simulation->iClock, widget->lWidgetNr, server->szServerName);
    if(queue->pHead != NULL)
         seize(simulation, queue, server);
    
}
/******************************leaveSystem***************************************
 *       void leaveSystem (Simulation simulation, Widget *widget)
 * * Purpose:
 *      exits a widget out the system and stores the total time.
 * Parameter:
 *      I Simulation simulation        The simulation passed in
 *      I Widget *widget               The widget current
 * Return:
 *      
 * 
 *****************************************************************************/
void leaveSystem(Simulation simulation, Widget *widget)
{
    int widgetSum;
    simulation->lWidgetCount = simulation->lWidgetCount + 1;
    widgetSum = simulation->iClock - widget->iArrivalTime;
    simulation->lSystemTimeSum = simulation->lSystemTimeSum + widgetSum;
    if(simulation->bVerbose == TRUE)
        printf("%4d    %2ld     Exit System, in System %d\n", simulation->iClock, widget->lWidgetNr, widgetSum);
    
    
}
/****************************runSimulationC**************************************
 * void runSimulationC(Simulation simulation)
 * Purpose:
 *      This function loops through the event list and implements the subroutines
 *      to calculate the statistics for alternative C.
 * Parameters:
 *     I Simulation simulation         simulation passed in with the event list
 * Notes:
 * 
 * Returns:
 *      
 * ****************************************************************************/

void runSimulationC(Simulation simulation)
{
    Queue queueW = newQueue("W");
    Server serverW = newServer("W");
    Event event;
    if(simulation->bVerbose == TRUE)
         printf("Time  Widget   Event\n");
    while(removeLL(simulation->eventList, &event))
    {
        simulation->iClock = event.iTime;
        switch(event.iEventType)
        {
            case EVT_ARRIVAL:
                arrival(simulation, &event.widget);
                if(event.widget.iWhichServer == 1 || event.widget.iWhichServer == 2)
                {
                    queueUp(simulation, queueW, &event.widget);
                    seize(simulation, queueW, serverW);
                }
                break;
            case EVT_SERVERW_COMPLETE:
                release(simulation, queueW, serverW, &event.widget);
                leaveSystem(simulation, &event.widget);
                break;
            default:
                errExit("Unknown event type: %d\n", event.iEventType);
             
        }
    }
    if(simulation->bVerbose == TRUE)
        printf("%4d     Simulation complete for Alternative A\n\n", simulation->iClock);
    printf("\tAverage Queue Time for Server W = %.1lf \n", (double)queueW->lQueueWaitSum/queueW->lQueueWidgetTotalCount);
    printf("\tAverage Time in System = %.1lf \n", (double)simulation->lSystemTimeSum /simulation->lWidgetCount);
        
}

/****************************runSimulationA**************************************
 * void runSimulationA(Simulation simulation)
 * Purpose:
 *      This function loops through the event list and implements the subroutines
 *      to calculate the statistics for alternative A
 * Parameters:
 *     I Simulation simulation         simulation passed in with the event list
 * Notes:
 * 
 * Returns:
 *      
 * ****************************************************************************/

void runSimulationA(Simulation simulation)
{
    Queue queueW = newQueue("W");
    Queue queueM = newQueue("M");
    Server serverW = newServer("W");
    Server serverM = newServer("M");
    Event event;
    if(simulation->bVerbose == TRUE)
           printf("Time  Widget   Event\n");
    while(removeLL(simulation->eventList, &event))
    {
        simulation->iClock = event.iTime;
        switch(event.iEventType)
        {
            case EVT_ARRIVAL:
                arrival(simulation, &event.widget);
                if(event.widget.iWhichServer == 1)
                {
                    queueUp(simulation, queueM, &event.widget);
                    seize(simulation, queueM, serverM);
                }
                else if (event.widget.iWhichServer == 2)
                {
                    queueUp(simulation, queueW, &event.widget);
                    seize(simulation, queueW, serverW);
                }
                break;
            case EVT_SERVERM_COMPLETE:
                release(simulation, queueM, serverM, &event.widget);
                leaveSystem(simulation, &event.widget);
                break;
            case EVT_SERVERW_COMPLETE:
                release(simulation, queueW, serverW, &event.widget);
                leaveSystem(simulation, &event.widget);
                break;
            default:
                errExit("Unknown event type: %d\n", event.iEventType);
             
        }
    }
    if(simulation->bVerbose == TRUE)
        printf("%4d     Simulation complete for Alternative A\n\n", simulation->iClock);
    printf("\tAverage Queue Time for Server M = %.1lf   \n", (double)queueM->lQueueWaitSum/queueM->lQueueWidgetTotalCount);
    printf("\tAverage Queue Time for Server W = %.1lf \n", (double)queueW->lQueueWaitSum/queueW->lQueueWidgetTotalCount);
    printf("\tAverage Time in System = %.1lf \n", (double)simulation->lSystemTimeSum /simulation->lWidgetCount);
}
/****************************runSimulationB**************************************
 * void runSimulationB(Simulation simulation)
 * Purpose:
 *      This function loops through the event list and implements the subroutines
 *      to calculate the statistics for alternative B.
 * Parameters:
 *     I Simulation simulation         simulation passed in with the event list
 * Notes:
 * 
 * Returns:
 *      
 * ****************************************************************************/

void runSimulationB(Simulation simulation)
{
    Queue queueW = newQueue("W");
    Server serverW = newServer("W");
    Queue queueX = newQueue("X");
    Server serverX = newServer("X");
    Queue queueY = newQueue("Y");
    Server serverY = newServer("Y");
    Event event;
    if(simulation->bVerbose == TRUE)
        printf("Time  Widget   Event\n");
    while(removeLL(simulation->eventList, &event))
    {
        simulation->iClock = event.iTime;
        switch(event.iEventType)
        {
            case EVT_ARRIVAL:
                arrival(simulation, &event.widget);
                queueUp(simulation, queueW, &event.widget);
                seizeAlternativeB(simulation, queueW, serverW);
                break;
                
            case EVT_SERVERW_COMPLETE:
                releaseAlternativeB(simulation, queueW, serverW,&event.widget);
                if(event.widget.iWhichServer == 1)
                {
                    queueUp(simulation, queueX, &event.widget);
                    seizeAlternativeB(simulation, queueX, serverX);
                }
                else if (event.widget.iWhichServer == 2)
                {
                    queueUp(simulation, queueY, &event.widget);
                    seizeAlternativeB(simulation, queueY, serverY);
                }
                break;
            case EVT_SERVERX_COMPLETE:
                releaseAlternativeB(simulation, queueX, serverX, &event.widget);
                leaveSystem(simulation, &event.widget);
                break;
            case EVT_SERVERY_COMPLETE:
                releaseAlternativeB(simulation, queueY, serverY, &event.widget);
                leaveSystem(simulation, &event.widget);
                break;
            default:
                errExit("Unknown event type: %d\n", event.iEventType);
                
                
                
        }
    }
    if(simulation->bVerbose == TRUE)
        printf("%4d     Simulation complete for Alternative B\n\n", simulation->iClock);
    printf("\tAverage Queue Time for Server W = %.1lf   \n", (double)queueW->lQueueWaitSum/queueW->lQueueWidgetTotalCount);
    printf("\tAverage Queue Time for Server X = %.1lf \n", (double)queueX->lQueueWaitSum/queueX->lQueueWidgetTotalCount);
    printf("\tAverage Queue Time for Server Y = %.1lf \n", (double)queueY->lQueueWaitSum/queueY->lQueueWidgetTotalCount);
    printf("\tAverage Time in System = %.1lf \n", (double)simulation->lSystemTimeSum /simulation->lWidgetCount);
}




/******************** processCommandSwitches *****************************
    void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName
        , char **ppszQueryFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.  
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszCustomerFileName     Customer File Name to return
    O   char **ppszQueryFileName        Query File Name to return 
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], Simulation simulation)
{
    int i;
    // Examine each of the command arguments other than the name of the program.
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, "expected switch in command line, found ", argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
        case 'v': 
            
            simulation->bVerbose = TRUE;
            break;
        case 'a':
            if(argv[i][2] == 'C')
                runSimulationC(simulation);
            if(argv[i][2]== 'A')
                runSimulationA(simulation);
            if(argv[i][2]== 'B')
                runSimulationB(simulation);
            break;
     
        case '?':
            exitUsage(USAGE_ONLY, "", "");
            break;
        default:
            exitUsage(i, "expected switch in command line, found ", argv[i]);
        }
    }
}

/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    In general, this routine optionally prints error messages and diagnostics.
    It also prints usage information.

    If this is an argument error (iArg >= 0), it prints a formatted message 
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits 
    with ERR_COMMAND_LINE.

    If this is a usage error (but not specific to the argument), it prints 
    the specific message and its supplemental diagnostic information.  It 
    also shows the usage and exist with ERR_COMMAND_LINE. 

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript or control:
                                    > 0 - command argument subscript
                                    0 - USAGE_ONLY - show usage only
                                    -1 - USAGE_ERR - show message and usage
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    switch (iArg)
    {
        case USAGE_ERR:
            fprintf(stderr, "Error: %s %s\n"
                , pszMessage
                , pszDiagnosticInfo);
            break;
        case USAGE_ONLY:
            break;
        default:
            fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
                , iArg
                , pszMessage
                , pszDiagnosticInfo);
    }
    // print the usage information for any type of command line error
    fprintf(stderr, "p2 -c customerFileName -q queryFileName\n");
    if (iArg == USAGE_ONLY)
        exit(USAGE_ONLY); 
    else 
        exit(ERR_COMMAND_LINE);
}


int main(int argc, char *argv[])
{
    
    Simulation simulation = newSimulation();
    
    readsInput(simulation);
    processCommandSwitches(argc,argv,simulation);
     
    return 0;
   
}



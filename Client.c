// Applicaiton A sending time                                                                                                                                                      
#include <zmq.h>                                                                                       
#include <string.h>                                                                                    
#include <stdio.h>                                                                                     
#include <unistd.h>                                                                                    
#include <time.h>                                                                                                      
int main (void)                                                                                        
{                                                   

/*Define parameters form time and buffer*/
  time_t rawtime;
  struct tm * timeinfo;
  char formatedTime[20];
  char buffer [10];

    printf ("Connecting to Time receiver…\n");                                                                                                                                                      
    /*Initial a new link */                                                                             
    void *context = zmq_ctx_new ();                                                                    
    void *requester = zmq_socket (context, ZMQ_REQ);                                                   
    /*using TCP  protocol, using 5555 port*/                                                          
    zmq_connect (requester, "tcp://localhost:5555");                                                   


    int request_nbr; //request numbers, transmit ten times                                                                                    
    for (request_nbr = 0; request_nbr != 10; request_nbr++)
    {                                          
        /*Get the current time, and format it into requested format*/
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        strftime(formatedTime,sizeof(formatedTime), "%Y/%m/%d %H:%M:%S",timeinfo);                                                                    
        /*sending time and get feedback*/                                        
        printf("Sending time %s\n", formatedTime);
        zmq_send (requester, formatedTime, 20, 0); //send time to the other application                                                           
        zmq_recv (requester, buffer, 10, 0);//receive feed back
        printf ("Received Feedback %d\n", request_nbr);                                    
    }                                                                                                                                                                                                    
    zmq_close (requester); //close the link                                                                         
    zmq_ctx_destroy (context);                                                                         
                                                                                                       
    return 0;                                                                                          
}
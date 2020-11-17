// Application B receive and display time 
#include <stdio.h>                                                                                                                                                          
#include <unistd.h>                                                                                    
#include <string.h>                                                                                    
#include <assert.h>                                                                                    
#include <zmq.h>                                                                                     
                                                                                                       
int main (void)                                                                                        
{                                                                                                      
    //  Initial a link use Socket to talk to clients via port 5555                                                                      
    void *context = zmq_ctx_new ();                                                                    
    void *responder = zmq_socket (context, ZMQ_REP);                                                   
    int rc = zmq_bind (responder, "tcp://*:5555");                                                     
    assert (rc == 0);                                                                                  
                                                                                                       
    while (1) {                                                                                        
        char buffer [20];                                                                              
        zmq_recv (responder, buffer, 20, 0);// receive time                                                             
        printf ("Received time %s\n", buffer);
        sleep (1);// add a delay          
        zmq_send (responder, "Received", 9, 0);                                                                                                                           
    }                                                                                                  
    return 0;                                                                                          
}
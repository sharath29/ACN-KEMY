

#include "kemy-queue-disc.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "ns3/double.h"
#include "ns3/simulator.h"
#include "ns3/abort.h"

#include "ns3/drop-tail-queue.h"
#include "ns3/net-device-queue-interface.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("KemyQueueDisc");

NS_OBJECT_ENSURE_REGISTERED (KemyQueueDisc);

TypeId KemyQueueDisc::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::KemyQueueDisc")
    .SetParent<QueueDisc> ()
    .SetGroupName("TrafficControl")
    .AddConstructor<KemyQueueDisc> ()
    
  ;

  return tid;
}

KemyQueueDisc::KemyQueueDisc () :
  QueueDisc ()
{
  NS_LOG_FUNCTION (this);
       
            const char * filename = getenv("WHISKERS");
        	if ( !filename ) {
        		fprintf( stderr, "KemyQueue: Missing WHISKERS environment variable.\n" );
        		throw 1;
        	}

        	/* open file */
        	int fd = open( filename, O_RDONLY );
        	if ( fd < 0 ) {
        		perror( "open" );
        		throw 1;
        	}

        	/* parse whisker definition */
        	KemyBuffers::WhiskerTree tree;
        	if ( !tree.ParseFromFileDescriptor( fd ) ) {
        		fprintf( stderr, "KemyQueue: Could not parse whiskers in \"%s\".\n", filename );
        		throw 1;
        	}

        	/* close file */
        	if ( ::close( fd ) < 0 ) {
        		perror( "close" );
        		throw 1;
        	}

        	/* store whiskers */
        	_whiskers = new WhiskerTree( tree );

	      
}

KemyQueueDisc::~KemyQueueDisc ()
{
  NS_LOG_FUNCTION (this);
}

void
KemyQueueDisc::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  
  QueueDisc::DoDispose ();
}



bool
KemyQueueDisc::DoEnqueue (Ptr<QueueDiscItem> item)
{
  NS_LOG_FUNCTION (this << item);

  

  bool retval = GetInternalQueue (0)->Enqueue (item);

  // If Queue::Enqueue fails, QueueDisc::DropBeforeEnqueue is called by the
  // internal queue because QueueDisc::AddInternalQueue sets the trace callback

  NS_LOG_LOGIC ("Number packets " << GetInternalQueue (0)->GetNPackets ());
  NS_LOG_LOGIC ("Number bytes " << GetInternalQueue (0)->GetNBytes ());

  return retval;
}

/*
 * Note: if the link bandwidth changes in the course of the
 * simulation, the bandwidth-dependent Kemy parameters do not change.
 * This should be fixed, but it would require some extra parameters,
 * and didn't seem worth the trouble...
 */
void
KemyQueueDisc::InitializeParams (void)
{
  NS_LOG_FUNCTION (this);
  NS_LOG_INFO ("Initializing Kemy params.");

 
}



Ptr<QueueDiscItem>
KemyQueueDisc::DoDequeue (void)
{
  NS_LOG_FUNCTION (this);

  if (GetInternalQueue (0)->IsEmpty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }
  else
    {
      
      Ptr<QueueDiscItem> item = GetInternalQueue (0)->Dequeue ();

      NS_LOG_LOGIC ("Popped " << item);

      NS_LOG_LOGIC ("Number packets " << GetInternalQueue (0)->GetNPackets ());
      NS_LOG_LOGIC ("Number bytes " << GetInternalQueue (0)->GetNBytes ());

      return item;
    }
}

Ptr<const QueueDiscItem>
KemyQueueDisc::DoPeek (void) const
{
  NS_LOG_FUNCTION (this);
  if (GetInternalQueue (0)->IsEmpty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  Ptr<const QueueDiscItem> item = GetInternalQueue (0)->Peek ();

  NS_LOG_LOGIC ("Number packets " << GetInternalQueue (0)->GetNPackets ());
  NS_LOG_LOGIC ("Number bytes " << GetInternalQueue (0)->GetNBytes ());

  return item;
}

bool
KemyQueueDisc::CheckConfig (void)
{
  NS_LOG_FUNCTION (this);

  return true;
}

} // namespace ns3

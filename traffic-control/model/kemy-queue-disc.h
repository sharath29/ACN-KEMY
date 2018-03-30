

#ifndef KEMY_QUEUE_DISC_H
#define KEMY_QUEUE_DISC_H

#include "ns3/queue-disc.h"
#include "ns3/nstime.h"
#include "ns3/boolean.h"
#include "ns3/data-rate.h"
#include "ns3/random-variable-stream.h"
#include "ns3/whiskertree.hh"
namespace ns3 {

class TraceContainer;

/**
 * \ingroup traffic-control
 *
 * \brief A KEMY packet queue disc
 */
class KemyQueueDisc : public QueueDisc
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * \brief KEMYQueueDisc Constructor
   *
   * Create a KEMY queue disc
   */
  KemyQueueDisc ();

  /**
   * \brief Destructor
   *
   * Destructor
   */ 
  virtual ~KemyQueueDisc ();


protected:
  /**
   * \brief Dispose of the object
   */



         WhiskerTree*  _whiskers;
        Memory _memory;
        unsigned int _the_window;
	    int summarystats;

	    int qib_;       	

  virtual void DoDispose (void);

private:
  virtual bool DoEnqueue (Ptr<QueueDiscItem> item);
  virtual Ptr<QueueDiscItem> DoDequeue (void);
  virtual Ptr<const QueueDiscItem> DoPeek (void) const;
  virtual bool CheckConfig (void);

  /**
   * \brief Initialize the queue parameters.
   *
   * Note: if the link bandwidth changes in the course of the
   * simulation, the bandwidth-dependent KEMY parameters do not change.
   * This should be fixed, but it would require some extra parameters,
   * and didn't seem worth the trouble...
   */
  virtual void InitializeParams (void);

};

}; // namespace ns3

#endif // KEMY_QUEUE_DISC_H

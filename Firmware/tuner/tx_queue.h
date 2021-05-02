/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   tx_queue.h
 * Author   :   Vishnu Dodballapur
 * Date     :   03/10/2021
 * Brief    :   defines related to queueing
 *******************************************************************************/

#ifndef TX_QUEUE_H_
#define TX_QUEUE_H_

#include <stdlib.h>  // for size_t

/*
 * Function     :   int tx_enqueue(void *buf, size_t nbyte)
 * Brief        :   Enqueues data onto the FIFO, up to the limit of the available FIFO
 *                  capacity.
 * Inputs       :   buf - Pointer to the data
 *                  nbyte - Max number of bytes to enqueue
 * Returns      :   The number of bytes actually enqueued, which could be 0. In case
 *                  of an error, returns -1.
 */
int tx_enqueue(void *buf, size_t nbyte);
/*
 * Function     :   int tx_dequeue(void *buf, size_t nbyte)
 * Brief        :   Attempts to remove ("dequeue") up to nbyte bytes of data from the
 *                  FIFO. Removed data will be copied into the buffer pointed to by buf.
 * Inputs       :   buf - Destination for the dequeued data
 *                  nbyte - Bytes of data requested
 *
 * Returns      :   The number of bytes actually copied, which will be between 0 and
 *                  nbyte.
 *
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * tx_dequeue.
 */
int tx_dequeue(void *buf, size_t nbyte);
/*
 * Function     :   size_t tx_length()
 * Brief        :   Returns the number of bytes currently on the FIFO.
 * Returns      :   Number of bytes currently available to be dequeued from the FIFO
 */
size_t tx_length();
/*
 * Function     :   size_t tx_capacity()
 * Brief        :   Returns the FIFO's capacity
 * Returns      :   The capacity, in bytes, for the FIFO
 */
size_t tx_capacity();

#endif /* TX_QUEUE_H_ */

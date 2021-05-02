/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   tx_queue.c
 * Author   :   Vishnu Dodballapur
 * Date     :   03/10/2021
 *******************************************************************************/

#include "tx_queue.h"
#include <string.h>
#include <stdint.h>

//Queue defines
#define CBFIFO_CAP 128
#define CBFIFO_CAP_MASK 0x7F

//Queue variables
static uint8_t cbfifo[CBFIFO_CAP];
static int cbfifo_len = 0;
static int rd_ptr = 0;
static int wr_ptr = 0;

//Function prototypes
int write_to_txqueue(void *src, size_t bytes_to_wr);
int read_from_txqueue(void *dest, size_t bytes_to_rd);

/*
 * Function     :   int tx_enqueue(void *buf, size_t nbyte)
 * Brief        :   Enqueues data onto the FIFO, up to the limit of the available FIFO
 *                  capacity.
 * Inputs       :   buf - Pointer to the data
 *                  nbyte - Max number of bytes to enqueue
 * Returns      :   The number of bytes actually enqueued, which could be 0. In case
 *                  of an error, returns -1.
 */
int tx_enqueue(void *buf, size_t nbyte)
{
   int bytes_to_wr = nbyte;

   if (buf == NULL)
   {
      return -1;
   }

   if (bytes_to_wr + cbfifo_len >= CBFIFO_CAP)
   {
      bytes_to_wr = CBFIFO_CAP - cbfifo_len;
   }

   if (bytes_to_wr == 0)
   {
      return bytes_to_wr;
   }
   bytes_to_wr = write_to_txqueue(buf, bytes_to_wr);

   wr_ptr = (wr_ptr + bytes_to_wr) & CBFIFO_CAP_MASK;
   cbfifo_len += bytes_to_wr;

   return bytes_to_wr;
}

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
int tx_dequeue(void *buf, size_t nbyte)
{
   int bytes_to_rd = nbyte;

   if (buf == NULL)
   {
      return -1;
   }

   if (bytes_to_rd > cbfifo_len)
   {
      bytes_to_rd = cbfifo_len;
   }

   if (bytes_to_rd == 0)
   {
      return bytes_to_rd;
   }
   bytes_to_rd = read_from_txqueue(buf, bytes_to_rd);
   rd_ptr = (rd_ptr + bytes_to_rd) & CBFIFO_CAP_MASK;
   cbfifo_len -= bytes_to_rd;

   return bytes_to_rd;
}

/*
 * Function     :   size_t tx_length()
 * Brief        :   Returns the number of bytes currently on the FIFO.
 * Returns      :   Number of bytes currently available to be dequeued from the FIFO
 */
size_t tx_length()
{
   return cbfifo_len;
}

/*
 * Function     :   size_t tx_capacity()
 * Brief        :   Returns the FIFO's capacity
 * Returns      :   The capacity, in bytes, for the FIFO
 */
size_t tx_capacity()
{
   return CBFIFO_CAP;
}

/*
 * Function     :   int write_to_txqueue(void *src, size_t bytes_to_wr)
 * Brief        :   Writes data into cbfifo
 * Inputs       :   src - Source for the data
 *                  bytes_to_wr - Number of bytes to write
 * Returns      :   The number of bytes written
 */
int write_to_txqueue(void *src, size_t bytes_to_wr)
{
   int wr_div = 0;

   if (wr_ptr + bytes_to_wr >= CBFIFO_CAP)
   {
      wr_div = CBFIFO_CAP - wr_ptr;
      memcpy(&cbfifo[wr_ptr], &((uint8_t *)src)[0], wr_div);
      memcpy(&cbfifo[0], &((uint8_t *)src)[wr_div], bytes_to_wr - wr_div);
   }
   else
   {
      memcpy(&cbfifo[wr_ptr], &((uint8_t *)src)[0], bytes_to_wr);
   }
   return bytes_to_wr;
}

/*
 * Function     :   int read_from_txqueue(void *dest, size_t bytes_to_rd)
 * Brief        :   Reads data from cbfifo
 * Inputs       :   dest - Destination for the data
 *                  bytes_to_rd - Number of bytes to read
 * Returns      :   The number of bytes read
 */
int read_from_txqueue(void *dest, size_t bytes_to_rd)
{
   int rd_div = 0;

   if (rd_ptr + bytes_to_rd >= CBFIFO_CAP)
   {
      rd_div = CBFIFO_CAP - rd_ptr;
      memcpy(&((uint8_t *)dest)[0], &cbfifo[rd_ptr], rd_div);
      memcpy(&((uint8_t *)dest)[rd_div], &cbfifo[0], bytes_to_rd - rd_div);
   }
   else
   {
      memcpy(&((uint8_t *)dest)[0], &cbfifo[rd_ptr], bytes_to_rd);
   }
   return bytes_to_rd;
}



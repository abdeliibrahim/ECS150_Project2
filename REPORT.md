# ECS 150 - uThread Library Report

## Phase 1 - Queueing

For developing a queue library, we needed to decide on a data structure that
would make it FIFO-compatible while also making it perform various operations
in O(1) time. For such requirements, we opted for a linked-list structure. We
began by creating a node struct that contained a value and a next node. Then, we
created the queue struct, containing a head and tail node, along with a count
variable.

### Create

For queue creation, we simply allocate memory for the queue, then set the head
& tail nodes to null, count to 0, and return the queue.

### Destroy

For destroying an empty queue, we call the "free" function on @queue, which
deallocates the memory. This only happens if @queue is empty.

### Dequeue

When dequeuing, we first declare a node "decapitated" (the node that will be
dequeued), setting it to the head of our @queue. We set out @data pointer to
the decapitated value; we set our current head to the next item in the
queue and decrementing the count. If our new head is equal to null, we update
our tail to also equal null. Then we deallocate our decapitated node, since
it is no longer any use.

### Delete

Deleting a queued item is quite simple. We first check if the targeted value is
the head, for which we can just dequeue as above. Otherwise, we iterate through
the queue, and once our target is found, we tie the node previous to the target
to the target's next node, then deallocate the deleted node.

### Iterate

To iterate through a queue, we set a node called "next" (not to be confused with
the next node that exists with every node), setting it to the current node's
next node, then calling our function on the current node's value. Finally, we
set the current node to next.

### Length

Length simply returns the queue's count value. -1 if the queue is empty.

## Phase 2 - Threading

For threading, we use a struct for our thread control block, containing a context,
state integer, dedicated stack, thread ID, and the TCB of the next thread in the
queue. We also globally declare a "current" thread control block.

To create a thread

00000000000000000000000000000000000000000000000000000000000000000000000000000000
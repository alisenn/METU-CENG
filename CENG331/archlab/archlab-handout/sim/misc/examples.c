/* Architecture Lab Part A, METU 2020 */

/* $begin examples */
struct list {
    long value;
    struct list *next;
};

/* Note that (void *) 0 is how NULL is defined in C.
   Basically, NULL should correspond to zero in your
   y86-64 code, nothing confusing! */

/* Reverse a linked list iteratively */
struct list *rev(struct list *head)
{
    struct list *prev = (void *) 0;

    while (head) {
        struct list *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}


/* Reverse a linked list recursively */
struct list *rrev(struct list *head)
{
    struct list *rev_head;

    if (!head || !head->next)       /* return if <= 1 element, w/ short circuit */
        return head;

    rev_head = rrev(head->next);    /* head->e1<-e2<-e3<-...<-rev_head */
    head->next->next = head;        /* head-><-e1<-e2<-e3<-...<-rev_head */
    head->next = (void *) 0;        /* head<-e1<-e2<-e3<-...<-rev_head */

    return rev_head;
}


/* Copy a block of data calculating its checksum, accounting for possible overlaps */
long move(long *dst, const long *src, long len)
{
    /* If we have an intersection like the following (len == 3):
           dst   src
           [ ][ ][ ][ ][ ]
       Copying as usual, dst[i] = src[i] in a loop 0->end, is fine! 
       But if we have it the other way around:
           src   dst
           [ ][ ][ ][ ][ ]
       Copying as usual will overwrite src's own elements! 
       Have to copy from end->0. */

    /* Assume we're on 64-bit Linux and long is 8 bytes */

    long dst_v = (long) dst;
    long src_v = (long) src;
    long checksum = 0;
    long step = 1;
    long elem_size = sizeof(long); 

    /* Default is forward, have to reverse if intersecting as shown above */
    if (src_v < dst_v && dst_v < src_v + elem_size * len) {
        /* Careful here! sizeof(long) * (len - 1) is added to dst and src */
        dst = dst + len - 1;
        src = src + len - 1;
        step = -1;
    }

    /* Finally, copy the values word by word... */
    while (len > 0) {
        checksum ^= *src;
        *dst = *src;
        dst += step;
        src += step;
        len--;
    }

    return checksum;
}
/* $end examples */

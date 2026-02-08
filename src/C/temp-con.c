
   printf("-------Testing con_insert.\n");
   *(int *)ip = 777;
   con_insert(sp, 55, ip);
   con_insert(sp, 66, ip);
   con_insert(sp, 77, ip);
   con_insert(sp, 88, ip);
   con_insert(sp, 99, ip);
   con_insert(sp, 44, ip);

   printf("-------Print sequence from beginning to the end.\n");
   con_open(sp);
   i = 0;
   while ((kp = con_read(sp)) != NULL) {
      printf("cnt=%d, key=%d, val=%d\n", i++, kp->key, *(int *)(kp->val));
   }
  
   printf("-------Testing con_lookup.\n");
   if ((kp = con_lookup(sp, 42)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 42);
   }
   if ((kp = con_lookup(sp, 88)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 88);
   }
   if ((kp = con_lookup(sp, 450)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 450);
   }
   if ((kp = con_lookup(sp, 500)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 500);
   }
   if ((kp = con_lookup(sp, 160)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 160);
   }
   if ((kp = con_lookup(sp, 33)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 33);
   }

   k = 600;
   printf("-------Print sequence from %d to the end.\n", k);
   con_open_at(sp, k);
   i = 0;
   while ((kp = con_read(sp)) != NULL) {
     printf("cnt=%d, key=%d, val=%d\n", i++, kp->key, *(int *)(kp->val));
   }

   printf("-------Disposing the sequence.\n");
   con_free(sp);

   // --------------------------------------
   
   printf("-------Creating kvs of 10 elements.\n");
   sp = con_alloc(10);

   int d = (i = 100000);
   printf("-------Inserting %d random kv pairs.\n", d);
   while (i-- > 0) {
      int k = rand() % d;
      set2_node *p = (set2_node *)malloc(sizeof(int));
      *p = k;
      if (!con_member(sp, k)) 
	 con_insert(sp, k, p);
   }
   printf("kvs size=%d.\n", con_size(sp));

   printf("-------Testing lookup().\n", d);
   i = 1000;
   while (i-- > 0) {
      int k = rand() % d;
      if ((kp = con_lookup(sp, k)) != NULL) {
         printf("Lookup: key=%d, val=%d\n", kp->key, *(kp->val));
      } else {
         printf("Lookup: no such key=%d\n", k);
      }
   }

   k = 99180;
   printf("-------Print sequence from %d to the end.\n", k);
   con_open_at(sp, k);
   i = 0;
   while ((kp = con_read(sp)) != NULL) {
     printf("cnt=%d, key=%d, val=%d\n", i++, kp->key, *(kp->val));
   }

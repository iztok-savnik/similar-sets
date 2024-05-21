#!/usr/bin/perl
#
# Usage: 
# ./check-similar.pl testset < dataset > results


sub check_similar {
   my $p1 = shift;
   my $p2 = shift;
   my $d1 = shift;
   my $d2 = shift;

   while (@$$p1 && @$$p2) {

      $ep1 = $$p1[0];
      $ep2 = $$p2[0];

      if ($ep1 == $ep2) {

         shift @$p1;
         shift @$p2;
         next;

      } else {

	 # delete an element from @p1
 	 if ($ep1 < $ep2) {

	    if ($$d1 > 0) {
	       shift @$p1;
	       $$d1--;
	       next;
	       
	    } else {

	       # no more deleting from @p1
	       return false;   
	    }
	   
	 } else { # $ep1 > $ep2

	    # delete an element from @p2
	    if ($$d2 > 0) {
	       shift @$p2;
	       $$d2--;
	       next;
	       
	    } else {

	       # no more deleting from @p2
	       return false;   
	    }
         }
      } 
   } # while

   # handle tails
   # first, equality
   if (!@$p1 && !@$p2) {

      # d1 and d2 are >= 0.
      return true;
   }
   
   if (!@$p1) {
    
      # true only if remaining elems from se can be skipped
      $$d2 -= @$p2;
      return ($$d2 >= 0);

   } else { 

      # true only if remaining elems from sp can be added
      $$d1 -= @$p1;
      return ($$d1 >= 0);
   }   
}

sub main_check_similar {

   # testset and dataset
   my (@ts,@ds);

   # testset file name
   $tsfn = $ARGV[0];

   # load testsets
   open(TS, '<', $tsfn);
   
   while(<FR>) {
      chop;
      my @ts = split " ";
      print "$_\n";
      

      # load datasets and check similar to testset
      while(<STDIN>) {
         chop;
         my @l = split " ";

	 if (&check_similar(\@ts, \@ds)) {
	    print (join " ", @ds)."\n";
	 }
      }
   }

   # close testset file
   close(TS);
   
}

&main_check_similar;




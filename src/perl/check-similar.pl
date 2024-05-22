#!/usr/bin/perl
#
# Usage: 
# ./check-similar.pl testset < dataset > results

use BerkeleyDB;

BEGIN {
  system "rm *.db\n";
}

# store dataset
tie @ds, 'BerkeleyDB::Recno',
         -Cachesize => 5000000000,
         -Filename   => "store.db",
         -Flags      => DB_CREATE;  #|DB_RDONLY;
@ds = ();

# check if two sets p1 and p2 are similar with respect to LCS.
sub check_similar {
   my $p1 = shift;
   my $p2 = shift;
   my @s1 = @$p1;
   my @s2 = @$p2;
   my $d1 = shift;
   my $d2 = shift;

   while (@s1 && @s2) {

      $e1 = $s1[0];
      $e2 = $s2[0];

      if ($e1 == $e2) {

         shift @s1;
         shift @s2;
         next;

      } else {

	 # shift an element from @s1 out
 	 if ($e1 < $e2) {

	    if ($$d1 > 0) {
	       shift @s1;
	       $$d1--;
	       next;
	       
	    } else {

	       # no more deleting from @s1
	       return 0;   
	    }
	   
	 } else { # $e1 > $e2

	    # shift an element from @s2 out
	    if ($$d2 > 0) {
	       shift @s2;
	       $$d2--;
	       next;
	       
	    } else {

	       # no more deleting from @s2
	       return 0;   
	    }
         }
      } 
   } # while

   # handle tails
   # first, equality
   if (!@s1 && !@s2) {

      # d1 and d2 are >= 0.
      return 1;
   }
   
   if (!@s1) {
    
      # true only if remaining elems from se can be skipped
      $$d2 -= @s2;
      return ($$d2 >= 0);

   } else { 

      # true only if remaining elems from sp can be added
      $$d1 -= @s1;
      return ($$d1 >= 0);
   }   
}

sub main_check_similar {

   # test set and data set
   my @t = ();
   my @d = ();
   my $d1;
   my $d2;
   my $str = "";
   
   # testset file name
   $tsfn = $ARGV[0];

   while (<STDIN>) {

      chop;
      $ds[$i++] = $_;
      #print "$_\n";
   }
   my $ds_size = scalar(@ds);

   # load testsets
   open(TS, '<', $tsfn);
   
   while(<TS>) {
      chop;
      my @t = split " ";
      $str = join " ", @t;
      print "? ".$str."\n";
      $d1 = ($d2 = 2);

      # if len of @t less than 2*d1 
      if ((scalar @t) < 2*$d1) {
	 #print "skipped\n";
	 next;
      }
      
      # go thru data sets and check similarity with current test set
      for (my $i = 0; $i <= ($ds_size - 1); $i++) {
         @d = split " ", $ds[$i];
         $d1 = ($d2 = 2);
	 
	 if (&check_similar(\@t, \@d, \$d1, \$d2)) {

	    $str = join " ", @d;
	    print $str."\n";
	 }
      }
   }

   # close testset file
   close(TS);
   
}

&main_check_similar;




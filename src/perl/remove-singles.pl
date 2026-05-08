#!/usr/bin/perl 
#
# Usage: 
# ./remove-singles.pl < dataset > dataset-1

#
# remove singles sets (sets with one element)
sub test_remove_singles {
    
   # counting sets
   my $i = 0;

   # thru lines
   while (<STDIN>) {

      # split input line into array @l
      chop;
      my @l = split " ";
      if ((scalar @l) > 1) { print $_."\n"; }

   }
}

&test_remove_singles;


#!/usr/bin/perl
#
# Usage: 
# ./gen-map-onfreq.pl < dataset.freq > dataset.freq.map

use BerkeleyDB;

BEGIN {
  system "rm map.db\n";
}

# a map from alphabet elements to to newly created ids
tie @freq, 'BerkeleyDB::Recno',
          -Cachesize => 3000000000,
          -Filename => "map.db",
          -Flags    => DB_CREATE;  # |DB_RDONLY;

@freq = ();

sub test_gen_map_onfreq {

   # counting sets
   my $i = 0;
   my (@l,@l1);
   my $trnk_hght = $ARGV[0];
   #print "trunk height = ".$trnk_hght."\n";

   # load frequencies and generate a mapping
   while(<STDIN>) {
      chop;
      my @l = split " ";
      
      # store elements by decreasing freq
      $freq[$i++] = $l[0]; 
   }

   # print trunk
   for ($i = 0; $i < $trnk_hght; $i++) {
      print $freq[$i]." ".($i + 1)."\n";
   }

   # print crown
   $i = scalar(@freq) - 1;
   my $k = $trnk_hght + 1;
   while ($i >= $trnk_hght) {
      print $freq[$i--]." ".$k++."\n";
   }
}

&test_gen_map_onfreq;




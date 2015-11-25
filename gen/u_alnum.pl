#!/usr/bin/perl
use warnings;
use strict;
use open qw{:std :utf8};

my @chrs;

open (my $unidata, "wget ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt -O- |") or die "Cannot download UnicodeData using wget: $!";

while (<$unidata>) {
  chomp;
  my @parts = split /;/, $_, -1;
  die "Bad line $_ in UnicodeData.txt" unless @parts == 15;

  my ($code, $name, $cat, $upper, $lower, $title) = @parts[0, 1, 2, 12, 13, 14];
  next unless $cat =~ /^[LMN]/;

  $code = hex($code);
  my $last_code = $code;
  if ($name =~ /^<(.*), First>$/) {
    my $range_name = $1;
    chomp (my $next_line = <$unidata>);
    my @next_parts = split /;/, $next_line, -1;
    my ($next_code, $next_name) = @next_parts[0, 1];
    $next_name =~ /^<$range_name, Last>$/ or die "Unrecognized end '$next_name' of range $range_name";
    $last_code = hex($next_code);
  }

  foreach my $point ($code..$last_code) {
    my $utf8 = chr($point);
    utf8::encode($utf8);
    push @chrs, $utf8;
  }
}
close $unidata;

for (my $i = 0; $i < @chrs; $i++) {
  print !$i ? "  u_alnum =" : " |";
  my $fst = ord(substr $chrs[$i], -1, 1);
  while ($i + 1 < @chrs && substr($chrs[$i], 0, -1) eq substr($chrs[$i+1], 0, -1) && ord(substr($chrs[$i], -1, 1)) + 1 == ord(substr($chrs[$i+1], -1, 1))) {
    $i++;
  }
  my $lst = ord(substr $chrs[$i], -1, 1);

  foreach my $byte (split //, substr($chrs[$i], 0, -1)) {
    print " " . ord($byte);
  }
  print " " . ($fst eq $lst ? $fst : "$fst..$lst");
}
print ";\n";

#!/usr/bin/perl


use File::Find;
use File::Basename;

find(
    {
        wanted => \&findfiles,
    },
    'src'
);



sub findfiles
{

    $header = <<EOH;
/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */
EOH

    $f = $File::Find::name;
    if ($f =~ m/\.h$/ or $f =~ m/.cpp$/)
    {
        #To search the files inside the directories
        print "Processing $f\n";

        $q = basename($f);
        print "$q\n";
        open(IN, "<$q") || die "Cant open IN $!";
        open(OUT, "> ${q}.bak") || die "Cant open BAK $!";

        $nonBlank = 0;
        $inComment = 0;
        while(<IN>)
        {
            if ($nonBlank)
            {
                print OUT
            }
            else
            {
                if (m:^\s*/\*:) {
                    $inComment = 1;
                }
                elsif (m:\s*\*/:)
                {
                    print OUT $header;
                    $nonBlank = true;
                    $inComment = false;
                }
                elsif ($inComment)
                {

                }
                elsif (m:^//:)
                {

                }
                else
                {
                    print OUT $header;
                    $nonBlank = true;
                    print OUT;

                }
            }
        }
        close(IN);
        close(OUT);
        system("mv ${q}.bak ${q}");
        system("clang-format -i ${q}");
    }
}

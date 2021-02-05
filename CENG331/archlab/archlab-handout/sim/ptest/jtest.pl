#!/usr/bin/perl 
#!/usr/local/bin/perl 
# Test jump instructions

use Getopt::Std;
use lib ".";
use tester;

cmdline();

@vals = (32, 64);

@instr = ("jmp", "jle", "jl", "je", "jne", "jge", "jg", "call");

# Create set of forward tests
foreach $t (@instr) {
    foreach $va (@vals) {
	foreach $vb (@vals) {
	    $tname = "jf-$t-$va-$vb";
	    open (YFILE, ">$tname.ys") || die "Can't write to $tname.ys\n";
	    print YFILE <<STUFF;
	      irmovq stack, %rsp
	      irmovq \$1, %rsi
	      irmovq \$2, %rdi
	      irmovq \$4, %rbp
	      irmovq \$$va, %rax
	      irmovq \$$vb, %rdx
	      subq %rdx,%rax
	      $t target
	      addq %rsi,%rax
	      addq %rdi,%rax
	      addq %rbp,%rax
              halt
target:
	      addq %rsi,%rdx
	      addq %rdi,%rdx
	      addq %rbp,%rdx
              nop
              nop
	      halt
.pos 0x100
stack:
STUFF
	    close YFILE;
	    &run_test($tname);
	}
    }
}

# Create set of backward tests
foreach $t (@instr) {
    foreach $va (@vals) {
	foreach $vb (@vals) {
	    $tname = "jb-$t-$va-$vb";
	    open (YFILE, ">$tname.ys") || die "Can't write to $tname.ys\n";
	    print YFILE <<STUFF;
	      irmovq stack, %rsp
	      irmovq \$1, %rsi
	      irmovq \$2, %rdi
	      irmovq \$4, %rbp
	      irmovq \$$va, %rax
	      irmovq \$$vb, %rdx
	      jmp skip
	      halt
target:
	      addq %rsi,%rdx
	      addq %rdi,%rdx
	      addq %rbp,%rdx
              nop
              nop
	      halt
skip:
	      subq %rdx,%rax
	      $t target
	      addq %rsi,%rax
	      addq %rdi,%rax
	      addq %rbp,%rax
              halt
.pos 0x100
stack:
STUFF
	    close YFILE;
	    &run_test($tname);
	}
    }
}


if ($testiaddq) {
    # Create set of forward tests using iaddq
    foreach $t (@instr) {
	foreach $va (@vals) {
	    foreach $vb (@vals) {
		$tname = "ji-$t-$va-$vb";
		open (YFILE, ">$tname.ys") || die "Can't write to $tname.ys\n";
	      print YFILE <<STUFF;
	      irmovq stack, %rsp
	      irmovq \$1, %rsi
	      irmovq \$2, %rdi
	      irmovq \$4, %rbp
	      irmovq \$$va, %rax
	      iaddq \$-$vb,%rax
	      $t target
	      addq %rsi,%rax
	      addq %rdi,%rax
	      addq %rbp,%rax
              halt
target:
	      addq %rsi,%rdx
	      addq %rdi,%rdx
	      addq %rbp,%rdx
              nop
              nop
	      halt
.pos 0x100
stack:
STUFF
                close YFILE;
		&run_test($tname);
	    }
	}
    }
}


if ($testjmpq) {
    # Create bunch of tests using jmpq
    @offsets = (0, 8, 16, 24, 32);
    @values = (2, 8, 32, 128);
    foreach $off (@offsets) {
	foreach $va (@values) {
		$tname = "jmpq-$off-$va";
		open (YFILE, ">$tname.ys") || die "Can't write to $tname.ys\n";
	      print YFILE <<STUFF;
	      irmovq stack, %rsp
	      irmovq \$1, %rsi
	      irmovq \$2, %rdi
	      irmovq \$4, %rbp
          irmovq \$8, %rcx
          irmovq \$16, %rdx
          irmovq \$32, %r8
	      irmovq \$$va, %rax
          irmovq jmptable, %r11
          irmovq \$$off, %r12
          addq %r12, %r11
          mrmovq (%r11), %r11
	      jmpq %r11
	      addq %rsi,%rax
	      addq %rdi,%rax
	      addq %rbp,%rax
              halt
.align 8
jmptable:
          .quad target0
          .quad target1
          .quad target2
          .quad target3
          .quad target4
target0:
          addq %rsi,%rcx
          addq %rdi,%rcx
          addq %rbp,%rcx
          halt
target1:
	      addq %rsi,%rdx
	      addq %rdi,%rdx
	      addq %rbp,%rdx
              nop
              nop
	      halt
target2:
          addq %rsi,%r8
          addq %rdi,%r8
          addq %rbp,%r8
          nop
          halt
target3:
          addq %rsi,%r9
          addq %rdi,%r9
          addq %rbp,%r9
          nop
          nop
          nop
          halt
target4:
          addq %rsi,%r10
          addq %rdi,%r10
          addq %rbp,%r10
          nop
          halt
.pos 0x300
stack:
STUFF
                close YFILE;
		&run_test($tname);
	}
	}
}

&test_stat();



    .data
arr:        .word 2, -4, 6, -8, 10   # Array of numbers
exitvalue:  .word 5                  # Exit condition (array length)
max_sum:    .word 0                   # Max subarray sum
current_sum: .word 0                  # Current subarray sum

    .text
    .globl main

main:
    la $t0, arr            # Load base address of arr into $t0
    lw $t1, exitvalue      # Load exit value (array length) into $t1
    lw $t2, 0($t0)         # Load arr[0] into $t2 (current_sum)
    sw $t2, current_sum     # Initialize current_sum
    sw $t2, max_sum        # Initialize max_sum

    li $t3, 1              # Initialize index i = 1

loop:
    beq $t3, $t1, done     # If i == exitvalue, jump to done

    mul  $t4, $t3, 4       # Multiply i by 4 to get byte offset for arr[i]
    add  $t5, $t0, $t4     # Compute address for arr[i]
    lw   $t6, 0($t5)       # Load arr[i] into $t6

    lw   $t2, current_sum   # Load current_sum into $t2
    add  $t2, $t2, $t6      # Update current_sum = current_sum + arr[i]

    # If current_sum < arr[i], reset current_sum to arr[i]
    blt  $t2, $t6, reset_sum

    # Update max_sum if current_sum is greater
    lw   $t7, max_sum      # Load max_sum into $t7
    bgt  $t2, $t7, update_max

    j continue_loop

reset_sum:
    move $t2, $t6          # Reset current_sum to arr[i]

update_max:
    move $t7, $t2          # Update max_sum with current_sum
    sw   $t7, max_sum      # Store updated max_sum

continue_loop:
    sw   $t2, current_sum   # Store updated current_sum
    addi $t3, $t3, 1       # Increment index i
    j loop                 # Repeat the loop

done:
    # Load the max_sum into $a0 for printing
    lw   $a0, max_sum      # Load max_sum into $a0
    li   $v0, 1            # syscall for print integer
    syscall

    li   $v0, 10           # Exit program
    syscall

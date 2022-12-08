# C Coding Guidelines

These coding conventions are modeled off of the convention used by David Cutler.
When in doubt, look at code written in minkernel\ntos\ke or xbox\lnm\ntos\ke to
decide how to handle a scenario not documented here. When appropriate, existing
code should be modified to adhere to the convention. If a legacy module does not
follow strict rules, then some rules do not need to be rigorously applied. All
new functions and modules should adhere to convention.

## Contents
- Prolog
- Module Layout
  - File Header
  - Includes
  - Function Prototypes
  - Macros
  - Type Definitions
- Checklist
- Globals
- alloc_text Pragmas
- Function Declarations and Definitions
- Variable Definition
- Structure definitions
- Typedef
- Comments
- Spacing and braces
- For statement
- While statement
- if ... then ... else statement
- Switch Statement
- Do Statement
- Goto statement
- Increment/Decrement operators
- &&, || operators in conditions
- Bitwise Operators
- Sizeof operator
- Indentation
- Breaking up lines
- Miscellaneous

## Prolog
- Never violate 80-column limit!

## Module Layout

A C-file should have the following file layout
- File Header
- Includes
- Hash defines
- Type definitions
- Function prototypes
- Pragmas
- Globals
- Function definitions

### File Header

All C-files must contain a file header at the top of the file. They should use
the provided template below.
```c
/*++

Copyright (c) 1989  Microsoft Corporation

Module Name:

    wait.c

Abstract:

    This module implements the generic kernel wait routines. Functions
    are provided to delay execution, wait for multiple objects, wait for
    a single object, or set a client event and wait for a server event.

    N.B. This module is written to be a fast as possible and not as small
        as possible. Therefore some code sequences are duplicated to avoid
        procedure calls. It would also be possible to combine wait for
        single object into wait for multiple objects at the cost of some
        speed. Since wait for single object is the most common case, the
        two routines have been separated.

Author:

    David N. Cutler (davec) 23-Mar-1989

    Arun Kishan (arunki) 28-Mar-2008

Environment:

    Kernel mode only.

--*/
```

### Includes

### Function Prototypes

- All functions should have a prototype defined with the appropriate scope
- Functions only used within a file should have their prototype in that file

    Function Prototype at the top of the file(waitsup.c)
```c
    VOID
    KiInsertPrcbWaitEntry (
        __inout PKTHREAD Thread,
        __inout PKPRCB Prcb
        );
```
    Function definition in the same file(waitsup.c)
```c
    VOID
    KiInsertPrcbWaitEntry (
        __inout PKTHREAD Thread,
        __inout PKPRCB Prcb
        )
```
- Functions whose scope is a library should have the prototype in a header file
  that is included by the rest of the library. Note that by following this
  convention, the 'static' keyword is not necessary.
- Function prototypes should be written using the following convention:
```c
    return-type
    function-name (
        sal_annotation type-name argument-name,
        sal_annotation type2-name argument2-name
        );
```
- Functions which do not take any arguments should have VOID in their
  definition/declaration as shown below
```c
    KINLINE
    ULONG
    KiGetCurrentReadySummary (
        VOID
        )
```

### Macros

- Macros defines are all caps and use an underscore "_" between each word in the
  definition name.
- There is no whitespace between hash defines, unless they take more than one
  line, e.g.,
```c
    #define DEFINITION_1 \
        <a long expression>

    #define DEFINITION_2 ...
```

### Type Definitions

## Checklist

- Function names are descriptive and avoid abbreviations.
- Function prototypes are in alphabetic order within a file.
- Function and Parameter names are Pascal-cased, e.g.
  KiPerformGroupConfiguration.
- Well-known acronyms used in the function names have only the first letter
  capitalized, e.g. AcpiProcessorStartDevice.
- A single space separates the function name and the opening parenthesis.
- A single newline separates the function comment from the declaration, and a
  single newline separates the comment from the opening curly brace.
- Exactly four spaces precede the SAL annotation for each argument.
- Only one space separates the SAL annotation, parameter type and the argument
  name.
- The closing is on its own line, indented four spaces.
```c
    NTSTATUS
    NpCancelWaiter (
        __inout PWAIT_QUEUE WaitQueue,
        __in PUNICODE_STRING NameOfPipe,
        __in NTSTATUS Completionstatus,
        __inout PLIST_ENTRY DeferredList
        )

    /*++

    Routine Description:

        This procedure cancels all waiters that are waiting for the named
        pipe to reach the listening state.  The corresponding IRPs are completed
        with Completionstatus.
```

## Globals

- Global variables are in alphabetic order within a file.
- Global variables may be divided into related groups but are in alphabetic
  order within these groups.
- Global variables are only initialized with non-zero values.

## Other

- `alloc_text` Pragmas:
    - All pageable, initialization, and page locked functions appear in an
      appropriate alloc_text pragma.
    - `alloc_text` pragmas are alphabetized by function name.
    - `alloc_text` pragmas have no blank lines between them.
- No whitespace should trail the last character of any line.  Enable your source
  editor to delete trailing whitespace on file save.

## Function Declarations and Definitions

- Space between function name and opening parenthesis
> Rationale: This convention makes searching for declaration/definition of a
function in basic text editors like Notepad so much predictable. For this to
work, callers of the function are expected to not have a space between the
function name and opening parenthesis. Ctrl+F -> function ( in the search box
will immediately take you to the definition/declaration of the function

- Each function will have its comment block between function definition and its
  body
```c
    NTSTATUS
    KiBeginThreadWait (
        __inout PKTHREAD Thread,
        __in KPROCESSOR_MODE WaitMode,
        __in KWAIT_REASON WaitReason,
        __in BOOLEAN Alertable
        )

    /*++

    Routine Description:

        This routine initiates an object wait sequence, establishing the wait
        reason, mode, and whether or not the wait is alterable. Once a thread
        is in this state, its wait can only be bypassed by an explicit abort
        issued by the thread or via an object-initiated thread signal.

        N.B. This routine immediately consumes any pending alert conditions.
             Kernel APCs are allowed to flush prior to entering the wait state,
             but do not abort the wait sequence.

    Arguments:

        Thread - Supplies a pointer to a dispatcher object of type thread.

        WaitMode - Supplies the processor mode associated with the wait.

        WaitReason - Supplies the wait reason.

        Alertable - Supplies a boolean value indicating whether or not the
            the wait is alertable.

    Return Value:

        NTSTATUS. If the wait sequence is prematurely aborted, a failure status
        is returned.

    --*/

    {
```
- Newline before and after each comment in the function body.
- A blank line between functions
- Newline after opening function brace and before start of code.
```c

    {

        PKMUTANT AbMutants[KI_MAXIMUM_MUTANT_SCAN];
        ULONG AbMutantsIndex;
```
- Do not arrange parameters in columns.
- Function name should use Pascal-Cased name.
- Function parameter names are Pascal-Cased.
```c
    return-type
    function-name (
        SALannotation type-name argument-name,
        SALannot type2-name argument-name
        )

    NTSTATUS
    BlockIoFirmwareRead (
        __in PBLOCK_IO_DEVICE BlockIoDevice,
        __out_ecount(NumberBlocks * BlockIoDevice->Information.BlockSize) PUCHAR Buffer,
        __in ULONGLONG BlockNumber,
        __in ULONGLONG NumberBlocks
        )
```
- Void function should have an empty return statement
```c
        return;
    }
```
- Boolean expressions can be used in return statements instead of full blown "if
  return else return " pattern
```c
        return (YieldReason != 0);
    }
```
- Variables and function parameters of type T *X are always written in their
  typedef'ed form (like PT X). Second level pointers like T **X is written as PT
  *X. And asterisk is always attached with the variable name not to the type
```c
    HV_SPA_PAGE_NUMBER
    MmpGetSpaPageNumberFromPage (
        __in PMMP_PHYSICAL_PAGE Page        <-----
        )
```
    And
```c
    BOOLEAN
    FASTCALL
    KiSignalSynchronizationObjectEx (
        __inout PKPRCB Prcb,
        __in PVOID Object,
        __deref_out_opt PKTHREAD *WakeThread    <---
        )
```

## Variable Definition

- Alphabetize local variables
- No multiple variable declarations
- Do not arrange variables in columns
- No single letter variables (i, j, k, etc.)
- InitialCapsFormat for all variables (Pascal Cased).
- Global variables begin with the component name.
- Words within a name are spelled out; abbreviations are discouraged
- Acronyms are treated as words, that is, on the first character of the acronym
  is capitalized
- Local variables are not initialized in their declarations
- Local variables are always declared at the beginning of a function
- Local variables need to be sorted based on their name not on their type!
```c
    HKEY DestSubKey;
    DWORD Index;
    DWORD MaxValueDataLength;
    DWORD MaxValueNameLength;
    HKEY SrcSubKey;
    DWORD Status;
    DWORD SubKeyLength;
    WCHAR SubKeyName[MAX_PATH];
    DWORD SubKeysCount;
    LPBYTE ValueData;
    DWORD ValueDataLength;
```
- Local variables are initialized in as tight a scope as possible
```c
    {

        LOGICAL DecrementStackCount;
        BOOLEAN Signal;
        PKTIMER Timer;

        NT_ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

        DecrementStackCount = FALSE;
        Signal = FALSE;
        Timer = &Thread->Timer;
```
- Do not perform redundant initializations( = {0}) or ZeroMemory on local
  variables (especially nonpointer types), like structure variables and
  primitive types, if they are guaranteed to  be initialized before their first
  usage.
```c
    {

        ETW_BUFFER_INFORMATION EtwBufferInfo;   <----
        ULONG LoggerId;
        NTSTATUS Status;

        //
        // Get the current ETW buffer info for the Circular Kernel Context Log
        //

        Status = EtwGetProcessorBuffer(CKCL_LOGGER_ID,
                                       KeGetCurrentPrcb()->Number,
                                       &EtwBufferInfo);  <----
```

## Structure definitions

- Structure definition should use capital letters.
- Type name should use "_" to separate the different parts of the name.
- Name of the defined struct should be the same name prefixed with "_".
```c
    struct _TPP_PH_LINKS {
        LIST_ENTRY Siblings;
        LIST_ENTRY Children;
        TPP_PH_KEY Key;
    };
```

## Typedef structs

- Type definitions should use capital letters.
- Name prefixed with "P" defined pointer to the defined type.
    typedef LONGLONG TPP_TIME, *PTPP_TIME;
- Typedef can be directly combined with a struct definition
```c
    typedef struct _TPP_BARRIER {
        volatile TPP_FLAGS_COUNT Ptr;
        RTL_SRWLOCK   WaitLock;
        TPP_ITE_WAITER WaitList;
    } TPP_BARRIER, *PTPP_BARRIER;
```

## Comments

- Newline before and after comment block
- Always have a line containing only "//" at start and end of comment block
- Don't comment obvious code (// return status)
- Comments approximate real sentences, and have real sentence structure, like
- Punctuation, capitalization, articles, and the like.
```c
    NpIrpWaitContext(Irp) = Context;

    //
    //  Acquire the spinlock.
    //

    KeAcquireSpinLock (&WaitQueue->SpinLock, &OldIrql);
```
- Parameter descriptions in function header comment blocks always start with
  "Supplies".  "Supplies a pointer to the thread data", for example.
- The "Return Value" section of a function comment block has all of its lines
  line up the same.
- If the function returns "VOID", the Return Value: in the comment block says
  "None."
```c
    NTSTATUS
    NpCancelWaiter (
        __inout PWAIT_QUEUE WaitQueue,
        __in PUNICODE_STRING NameOfPipe,
        __in NTSTATUS Completionstatus,
        __inout PLIST_ENTRY DeferredList
        )

    /*++

    Routine Description:

        This procedure cancels all waiters that are waiting for the named
        pipe to reach the listening state.  The corresponding IRPs are completed
        with Completionstatus.

    Arguments:

        WaitQueue - Supplies the wait queue being modified

        NameOfPipe - Supplies the name of the named pipe (device relative)
            that has just reached the listening state.

        CompletionStatus - Status to complete IRPs with

        DeferredList - List or IRPs to complete once we drop locks

    Return Value:

        None.

    --*/

    {
```
- Nota Bene comments are lined up with the right-hand side of the N.B.  For
  instance:
```c

    //
    // Body of the comment.
    //
    // N.B. This comment is lined up differently than a normal
    //      comment because it is a nota bene.
    //
```

## Spacing and braces

- Tabs expand to 4 spaces

## For statement

- For loop is broken down into multiple lines if the statement > 80 columns
- When a for loop is broken down into multiple lines, Then the body will start
  with a blank line
```c

    for (CollectionIndex = CollectionMin;
         CollectionIndex < CollectionMax;
         CollectionIndex += 1) {

        Tree = &KiTimer2Collections[CollectionIndex].Tree;
        RbNode = RtlRbGetMinNode(Tree);
```

## While statement

- Opening bracket on the same line as while statement
- One space between while and opening parenthesis
- No space between opening parenthesis and begin of conditional
- Brackets always used for while statement
- Closing bracket on a single line, aligned with while statement
```c
    while (*p != 0) {
        Ctx->AliasCount++;
        Length = (USHORT)((wcslen(p) + 1) * sizeof(WCHAR));
        Ctx->RequiredSize += sizeof(WCHAR) + Length + sizeof(ALIAS);
        p = (PWCH)((PCHAR)p + Length);
    }
```

## if then else statement

- Opening bracket on same line as if statement
- One space between if and opening parenthesis
- No space between opening parenthesis and begin of conditional
- One space after the comma separating parameters
- Brackets always used for if statements, even single-expression ones
- Else on the same lines as closing bracket of if block.
- A blank line follows an if/for/while/switch statement only if the conditional
  is multi-line.  Otherwise, no blank line.
```c
    if ((KeIsPrimaryNode(TargetNode) != FALSE) &&
        (KiActualNodeCost[Base + TargetNode->NodeNumber] == (ULONG64) -1)) {

        Offset = TargetNode->NodeNumber * KeNumberNodes +
                 SourceNode->NodeNumber;
```
- A blank line follows all closing curly braces, except ones followed
  immediately by another closing curly brace.
- A blank line follows every multiline function call. Except ones followed
  immediately by another closing curly brace.

Example 1:
```c
    PerformanceMask = KeQueryGroupAffinityEx(&HeteroConfig->PerformanceCores,
                                             Node->Affinity.Group);

    EfficiencyMask = KeQueryGroupAffinityEx(&HeteroConfig->EfficiencyCores,
                                            Node->Affinity.Group);
```
Example 2:
```c
    if ((Thread->ExplicitSystemHeteroCpuPolicy == FALSE) &&
        (Thread->UserHeteroCpuPolicy == KHeteroCpuPolicyDefault)) {

        KiSetHeteroPolicyThread(Thread,
                                KHeteroCpuPolicyDefault,
                                TRUE,
                                TRUE);
    }
```

- A blank line precedes every `} else` type line.
```c
    if (NamedPipeEnd == FILE_PIPE_SERVER_END) {
        ReadQueue = &Ccb->DataQueue[FILE_PIPE_INBOUND];

    } else {
        ReadQueue = &Ccb->DataQueue[FILE_PIPE_OUTBOUND];
    }
```

- A blank line is inserted before and after `#if defined(` or `#else` or `#elif`
  statements and the corresponding `#endif` lines.
```c
    #if defined(NP_USE_COMMON_FCB_HEADER)

        //
        // Non-paged mutex for the FSRTL_ADVANCED_FCB_HEADER structure.
        //

        FAST_MUTEX AdvancedFcbHeaderMutex;

    #endif

    } VCB, *PVCB;
```
- Blank lines precede and follow all asserts.  There are no blank lines between
  single line asserts.
```c
    //
    // Link this FCB into the list of pipes opened on the VCB and
    // into the name prefix lookup table.
    //

    ASSERT_EXCLUSIVE_VCB_PREFIX_TREE(Vcb);

    VERIFY(RtlInsertUnicodePrefix(&Vcb->PrefixTable,
                                  &Fcb->FileName,
                                  &Fcb->PrefixTableEntry));
```
- Multiple single line asserts do not have blank lines between them
```c
    KiGetVectorInterruptObject(
        __in ULONG Vector
        )
    {

        NT_ASSERT(Vector >= PRIMARY_VECTOR_BASE);
        NT_ASSERT(Vector <= MAXIMUM_IDTVECTOR);

        return KeGetCurrentPrcb()->VectorToInterruptObject[Vector - PRIMARY_VECTOR_BASE];
    }
```
- A blank line follows local variable declarations.
```c
    {

        PFCB Fcb;
        PWCH Name;
        USHORT Length;
        BOOLEAN StripBackSlash;
```

- Blank lines are avoided except where dictated by these rules.

## Switch Statement

- Opening bracket on the same line as the switch statement.
- One space between switch and opening parenthesis
- One space between case statement and constant value.
- Use braces in case statement only if you need to scope variables.
- For cases where case labels have scope, include the break statement outside
  the closing brace.
- Default case should be present.
- No blank line follows switch statement before the first case statement.
  Exception to this is if a comment begins after the switch condition
- No blank line follows the case statement before the first statement under the
  case label. Exception to this is if a comment begins after the case label
- In cases where a return or goto statement is used within a case statement,
  omit the break statement.

Example 1:
```c

        switch (Thread->PpmPolicy) {
        case ThreadPpmThrottle:
            ThreadQos = KHeteroCpuQosLow;
            break;

        case ThreadPpmSemiThrottle:
            ThreadQos = KHeteroCpuQosMedium;
            break;

        case ThreadPpmNoThrottle:
            ThreadQos = KHeteroCpuQosHigh;
            break;

        default:

            NT_ASSERT(FALSE);

            ThreadQos = KHeteroCpuQosDefault;
            break;
        }
```
Example 2: where comment rule causes a blank line after the switch statement and
before first case statement
```c
    switch (State) {

        //
        // Standby State.
        //
        // If the thread's priority is being lowered, then attempt
        // to find another thread to execute on the target processor.
        //

    case Standby:

        NT_ASSERT(Prcb != NULL);

        NT_ASSERT(Prcb->NextThread == Thread);

        NT_ASSERT(ARGUMENT_PRESENT(ReadyList));

        KiUpdateThreadPriority(Prcb, Thread, Priority, TRUE);
```

## Do Statement

- Always do body will have {} even if it has single statement
```c
    do {
        KeYieldProcessorEx(&SpinCount);
    } while ((ReadNoFence(&Event->Header.Lock) & KOBJECT_LOCK_BIT) != 0);
```

## Goto statement

- Gotos are acceptable for error cases, usually when going to the end of a
  function for cleanup.  The number of goto targets in a routine should almost
  never be more than 1.
```c
        if (!NpIsFileValid(FileObject)) {
            Status = STATUS_PIPE_DISCONNECTED;
            goto ExitAndRelease;
        }
        ...
    ExitAndRelease:

        NpReleaseExclusiveCcb (Ccb);

        return Status;

    }
```

## Increment/Decrement operators

- Always increment/decrement is done using += or -= not using ++ or –
```c
    for (Index = 0; Index < Count; Index += 1) {
        KiInitializeWaitBlock(WaitBlock,
                              Object[Index],
                              Thread,
                              WaitAll,
                              0);

        WaitBlock += 1;
```
  Or
```c
    if (Mutant->ApcDisable != 0) {

        NT_ASSERT(Mutant->ApcDisable == 1);

        Thread->KernelApcDisable -= 1;
    }
```

## &&, || operators in conditions

- Always when writing multiple conditions in if/while/for/assert predicate each
  sub predicate should be within () parenthesis
```c
    if ((Thread->SuspendSchedulerApcWait != FALSE) &&
        (Thread->FreezeCount != 0)) {
```
    Or
```c
    while ((SharedPrioritySet >= PrioritySet) &&
           (SharedPrioritySet >= LowPriorityMask)) {
```
- This is not followed with #if defined
```c
    #if defined(NT_SMT) && !defined(XBOX_SYSTEMOS)
```

## Bitwise Operators

- Always bitwise operators are surrounded with () parenthesis in conditionals.
  This is not followed so much in normal assignments
```c
    if ((Thread->WaitRegister.Flags &
         (KWAIT_STATUS_STATE_FLAGS | KWAIT_STATUS_SIGNAL_FLAGS)) ==
        (WaitInProgress << KWAIT_STATUS_STATE_BIT)) {
```

## Sizeof operator

- `sizeof` is a built-in unary operator that is statically evaluated by the
  compiler. Treat it like a function that takes any type and returns an unsigned
  integer. Parenthesize a sizeof type expression like a function call with a
  single parameter
- Use the variable itself to compute the size, rather than its data type. Not
  only does it remind the reader which symbol you are interested in, but it also
  doesn't break if the type of the variable changes (e.g. UINT16 gets changed to
  UINT32). Indentation

## Breaking up lines

- 80-character column length, unless keeping to this would require other rules
  to be broken.
- Statements should be kept on a single line if possible.
- If they must be on >1-line, function calls contain one parameter per line the
  first argument on the same line as the function name.
```c
    KiSetHeteroPolicyThread(Thread,
                            KHeteroCpuPolicyDefault,
                            TRUE,
                            TRUE);
```
- If this is still too long, line up all function parameters one-tab stop
  indented from the beginning of the function name.  This is a last resort.
- The closing parenthesis of a function call is on the same line as last
  argument.
```c
      Results = NpCommonRead(FileObject,
                             Buffer,
                             Length,
                             IoStatus,
                             NULL,
                             &DeferredList);
```
- break up complex conditionals on the operators (e.g. &&).  Make the operators
- at the end of the line and line up the two sub-expressions at the same column.
- If an assignment goes too long, break it just after the = sign. Add a blank
  line after the statement except ones followed immediately by another closing
  curly brace.
```c
    RootInHvCallDispatchVp =
        HvExtSchedulerAssistReadUChar(SchedulerAssistData,
                                      RootInHvCallDispatchVp);

    RootIsRunning = HvExtSchedulerAssistReadUChar(SchedulerAssistData,
                                                  RootIsRunning);
```
    Here are some additional multi-line statement examples following the above
    principles:
```c
    MaxBandwidthProfile =
        (PUQOS_OBJECT_MAX_BANDWIDTH_PROFILE)
        EQoSpGetPolicyProfile(Policy,
                              UQOS_OBJECT_TYPE_MAX_BANDWIDTH_PROFILE);

    Header->Next = (ULONG_PTR)Header->ObjectLength +
                 (ULONG_PTR)Header -
                 (ULONG_PTR)PolicyDescriptor;
```
- Prefer to break up statements at the outermost scope, not including the scope
  that the '=' sign is in in an assignment. (Note that this is not a hard rule.
  It may be better in some cases to place the line break at in inner scope,
  especially if doing so would result in fewer line breaks overall.) Prefer
  this:
```c
    NT_ASSERT(DescriptorSize >
             UQOS_SIZEOF_OBJECT_JOB_OBJECT_FILTER + sizeof(*Policy));
```
  to this:
```c
    NT_ASSERT(DescriptorSize > UQOS_SIZEOF_OBJECT_JOB_OBJECT_FILTER +
                               sizeof(*Policy));
```
  But prefer this:
```c
    Destination = Addend1 +
                  Addend2;
```
  to this:
```c
    Destination =
        Addend1 + Addend2;
```
And prefer this:
```c
    NT_ASSERT(Short > TooLongToFitTwoOfMeOnOneLine +
                         TooLongToFitTwoOfMeOnOneLine);
```
to this:
```c
    NT_ASSERT(Short >
                  TooLongToFitTwoOfMeOnOneLine +
                  TooLongToFitTwoOfMeOnOneLine)
```

- Subtle example, bitwise flags passed to a function call exceeding **80**
  columns is not broken.
```c
    Mdl = MmAllocateNodePagesForMdlEx(LowAddress,
                                      HighAddress,
                                      SkipBytes,
                                      PAGE_SIZE,
                                      MmNonCached,
                                      i,
                                      MM_DONT_ZERO_ALLOCATION | MM_ALLOCATE_FULLY_REQUIRED | MM_ALLOCATE_FROM_LOCAL_NODE_ONLY);
```

## Miscellaneous

- Tests are done as
  - `if (Variable == Value)`, not `if (Value == Variable)`.
  - `#if defined(` is used instead of `#ifdef`
- BOOLEAN tests are done as
  - `if (Variable == FALSE)` or `if (Variable != FALSE)` and `if (Variable != 0)`,
  - But not `if (Variable)`, `if (Variable == TRUE)`, or `if (!Variable)`
- Pointer NULL tests are done with
  - `if (Pointer == NULL)` or `if (Pointer !=  NULL)`,
  -  But not `if (Pointer)` or `if (!Pointer)`

> Rationale: This is because FALSE is defined as zero and TRUE is defined as
one. And generally, any non-zero number is considered TRUE. So, doing a check if
(Variable == TRUE) will only equate Variable for 1 not for other non-zero
values. Hence doing if (Variable != FALSE) is recommended.

```c
    if (Context == NULL) {
      return STATUS_INSUFFICIENT_RESOURCES;
    }
```
- Avoid use of the `static` keyword.
- Use of the ternary operator is discouraged; use an `if-else` construct instead.
- `#endif` always have single line comment of the condition used.
```c
    #endif // !defined(XBOX_SYSTEMOS)
```
- No space between cast and the expression.
```c
    if ((ULONG64)HalComparison >= ComputedCost) {
```
- Space between asterisk and type when casting to a pointer type
```c
    (PHAL_NODE_RANGE*)Buffer  // Wrong
    (PHAL_NODE_RANGE *)Buffer // Correct
```

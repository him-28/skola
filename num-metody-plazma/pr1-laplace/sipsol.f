      SUBROUTINE SIPSOL(ND,NSIP,AT,AL,AR,AB,B,X,ALPHA)                  ACZL0370
C***********************************************************************ACZL0371
C     (C)  COPYRIGHT  C. R. JESSHOPE  22-8-77                           ACZL0372
C***********************************************************************ACZL0373
C                                                                       ACZL0374
C     SUBROUTINE TO INVERT  AX=B  ITERATIVELY BY A STRONGLEY            ACZL0375
C     IMPLICIT PROCEEDURE AFTER H. L. STONE                             ACZL0376
C                                                                       ACZL0377
C     SIAM J. NUMER. ANAL.,5,P530,1968                                  ACZL0378
C                                                                       ACZL0379
C***********************************************************************ACZL0380
C     FORMAL PARAMETERS                                                 ACZL0381
C     -----------------                                                 ACZL0382
C                                                                       ACZL0383
C         ND - DUMMY DIMENSION FOR  AT....B                             ACZL0384
C         NSIP - DUMMY DIMENSION FOR ALPHA                              ACZL0385
C         AT - COEFFICIENT VECTOR FROM PDE DISCRETISATION  (TOP)        ACZL0386
C         AL - COEFFICIENT VECTOR FROM PDE DISCRETISATION  (LEFT)       ACZL0387
C         AR - COEFFICIENT VECTOR FROM PDE DISCRETISATION  (RIGHT)      ACZL0388
C         AB - COEFFICIENT VECTOR FROM PDE DISCRETISATION  (BOTTOM)     ACZL0389
C         X - SOLUTION VECTOR MUST CONTAIN TRAIL SOLUTION ON ENTRY      ACZL0390
C         B - RIGHT HAND SIDE OF DISCRETISED EQUATIONS                  ACZL0391
C         ALPHA - ARRAY/SCALAR CONTAINS ITERATION PARAMETER(S)          ACZL0392
C                                                                       ACZL0393
C***********************************************************************ACZL0394
C                                                                       ACZL0395
C     DISCRETISED EQUATIONS                                             ACZL0396
C     ---------------------                                             ACZL0397
C                                                                       ACZL0398
C     THE DISCRETISED EQUATIONS ARE NORMALISED SO THAT THE MAJOR        ACZL0399
C     DIAGONAL IS UNITY. THE I TH ELEMENTS OF  AT,AL,AR,AB  FORM THE    ACZL0400
C     I TH ROW OF A AS IN THE SCHEMATIC BELOW                           ACZL0401
C     SCANNING X THEN Y                                                 ACZL0402
C                                                                       ACZL0403
C                                                                       ACZL0404
C     ----->  X                                                         ACZL0405
C     1                                                                 ACZL0406
C     1                                                                 ACZL0407
C     1                              AT(I)                              ACZL0408
C     1                                1                                ACZL0409
C     V  Y                             1                                ACZL0410
C                                      1 1.0                            ACZL0411
C                            AL(I)-----X-----AR(I)                      ACZL0412
C                                      1                                ACZL0413
C                                      1                                ACZL0414
C                                      1                                ACZL0415
C                                    AB(I)                              ACZL0416
C                                                                       ACZL0417
C                                                                       ACZL0418
C***********************************************************************ACZL0419
C                                                                       ACZL0420
C     ITERATION PARAMETERS                                              ACZL0421
C     --------------------                                              ACZL0422
C                                                                       ACZL0423
C     THE ROUTINE REQUIRES EITHER A SCALAR OR A VECTOR ITERATION        ACZL0424
C     PARAMETER. IF THE MESH AND EQUATION HAVE A CONSTANT ANISOTRIPY    ACZL0425
C     A SCALAR PARAMETER ONLY IS NECESSARY                              ACZL0426
C                                                                       ACZL0427
C     -ACTION-  SET SW1 TO 0.0, NSIP TO 1 IN THE INITIALISATION, AND    ACZL0428
C     DIMENSION ALPHA ACCORDINGLEY IN THE MAIN PROGRAM                  ACZL0429
C                                                                       ACZL0430
C                                                                       ACZL0431
C     IF THE MESH OR EQUATION HAVE A VARIABLE ANISOTRIPY THEN A VECTOR  ACZL0432
C     OF PARAMETERS SHOULD BE USED                                      ACZL0433
C                                                                       ACZL0434
C     -ACTION- THIS IS THE DEFAULT ACTION SET IN THE PRE-INITIALISATION ACZL0435
C     CALL OF SUBROUTINE SIPNIT.  SHOULD REINITIALISATION BE NECESSARY  ACZL0436
C     THEN SET SW1 TO 1.0 NSIP TO ND, AND DIMENSION ALPHA IN THE        ACZL0437
C     MAIN PROGRAM ACCORDINGLEY                                         ACZL0438
C                                                                       ACZL0439
C     N.B.  NSIP AND ND SHOULD BE SET EQUAL TO THE DIMENSIONS OF        ACZL0440
C     THE ARRAYS THEY DUMMY DIMENSION,  IN THE MAIN PROGRAM             ACZL0441
C                                                                       ACZL0442
C     THE ITERATION PARAMETERS ARE CALCULATED AFTER STONE FOR THE       ACZL0443
C     DIFFUSION OPERATOR IN SUBROUTINE SIPARM, CALLED FROM THE          ACZL0444
C     POST INITIALISATION CALL OF SUBROUTINE SIPNIT                     ACZL0445
C                                                                       ACZL0446
C     N.B. A SCALAR PARAMETER CAN BE USED FOR THE CASE OF VARIABLE      ACZL0447
C     ANISOTRIPY, USING AN AVERAGE VALUE APPLIED OVER THE ENTIRE        ACZL0448
C     MESH.  HOWEVER THE CONVERGENCE RATE MAY BE ADVERSELY AFFECTED     ACZL0449
C                                                                       ACZL0450
C***********************************************************************ACZL0451
C                                                                       ACZL0452
C     STORAGE REQUIREMENTS                                              ACZL0453
C     --------------------                                              ACZL0454
C                                                                       ACZL0455
C         VECTOR PARAMETER - 10N + C                                    ACZL0456
C         SCALAR PARAMETER - 9N + C                                     ACZL0457
C                                                                       ACZL0458
C     WHERE N IS THE NUMBER OF MESH POINTS                              ACZL0459
C     AND C IS A CONSTANT                                               ACZL0460
C                                                                       ACZL0461
C***********************************************************************ACZL0462
      DIMENSION  AT(ND),AL(ND),AR(ND),AB(ND),X(ND),B(ND)                ACZL0463
      DIMENSION  ALPHA(NSIP)                                            ACZL0464
      DIMENSION  CYMULT(5)                                              ACZL0465
C***********************************************************************ACZL0466
C     COMMON VARIABLES                                                  ACZL0467
C     ----------------                                                  ACZL0468
C                                                                       ACZL0469
C     BLANK COMMON - CONTAINS 3072 ELEMENTS OF SCRATCH SPACE IN THIS    ACZL0470
C                  IMPLEMENTATION.  MUST CONTAIN AT LEAST 3*N ELEMENTS  ACZL0471
C                                                                       ACZL0472
C     LABELLED COMMON - EACH COMMON BLOCK CONTAINS A 10 WORD RECORD     ACZL0473
C                  (NOT ALL USED) WHICH WILL ALLOW FOR FUTURE EXPANSION ACZL0474
C                  AND INTERFACING.  FORTRAN INTEGER/REAL CONVENTIONS   ACZL0475
C                  ARE USED IN THE COMMON BLOCK NAMES TO INDICATE THE   ACZL0476
C                  WORD TYPE IN THE RECORD.                             ACZL0477
C                                                                       ACZL0478
C                                                                       ACZL0479
C     /NGEOM/  -  CONTAINS MESH GEOMETRY                                ACZL0480
C                                                                       ACZL0481
C         N - NUMBER OF MESH POINTS                                     ACZL0482
C         NOX - NUMBER OF INTERVALS IN THE X DIRECTION                  ACZL0483
C         NOY - NUMBER OF INTERVALS IN THE Y DIRECTION                  ACZL0484
C                                                                       ACZL0485
C     /NCHAN/  -  FORTRAN CHANNEL NUMBERS                               ACZL0486
C                                                                       ACZL0487
C         NIN - CARD INPUT  DEFAULT = 1                                 ACZL0488
C         NPM - PRINTER MONITOR CHANNEL  DEFAULT = 2                    ACZL0489
C         NPO - PRINTER MAIN OUTPUT  DEFAULT = 6                        ACZL0490
C                                                                       ACZL0491
C     /SIPCON/  -  SIP CONTROL IMFORMATION                              ACZL0492
C                                                                       ACZL0493
C         CHECK - INITIALISATION CHECK VARIABLE                         ACZL0494
C         ACC - FRACTIONAL EXIT ACCURACY  DEFAULT = 1.0E-5              ACZL0495
C         FAILCN - FAILSAFE EXIT FOR CONVERGENCE FAILURE  DEFAULT = 20. ACZL0496
C         SW1 - CONTROLS LOCAL/GLOBAL ITERATION PARAMETER  DEFAULT = 1.0ACZL0497
C                   1.0 = LOCAL PARAMETER                               ACZL0498
C                   0.0 = GLOBAL PARAMETER                              ACZL0499
C                   ELSE  ACTION UNDEFINED                              ACZL0500
C         SW2 - CONTROLS LEVEL OF OUTPUT  DEFAULT = 1.0                 ACZL0501
C                   1.0 = FULL OUTPUT                                   ACZL0502
C                   0.0 = MINIMAL OUTPUT                                ACZL0503
C                   ELSE  ACTION UNDEFINED                              ACZL0504
C                                                                       ACZL0505
C***********************************************************************ACZL0506
      COMMON  TU1(1024),TU2(1024),W(1024)                               ACZL0507
      COMMON  /NGEOM/N,NOX,NOY,NOUSE1(7)                                ACZL0508
      COMMON  /NCHAN/NIN,NPM,NPO,NOUSE2(7)                              ACZL0509
      COMMON  /SIPCON/CHECK,ACC,FAILCN,SW1,SW2,UNUSE1(5)                ACZL0510
C***********************************************************************ACZL0511
C     SET UP A CYCLE OF SCALING FACTORS FOR THE ITERATION CYCLE         ACZL0512
C***********************************************************************ACZL0513
      DATA  CYMULT/1.0,0.99,0.9,0.5,0.0/                                ACZL0514
C***********************************************************************ACZL0515
C     COMPUTE LOOP BOUNDS                                               ACZL0516
C***********************************************************************ACZL0517
      N1=NOX+1                                                          ACZL0518
      N2=NOX+2                                                          ACZL0519
      N3=N-N1                                                           ACZL0520
      N4=N-NOX                                                          ACZL0521
      N5=N-1                                                            ACZL0522
C***********************************************************************ACZL0523
C     COMPUTE RESIDUALS OVERWRITING B                                   ACZL0524
C***********************************************************************ACZL0525
      B(1)=B(1)-X(1)-AR(1)*X(2)-AB(1)*X(N2)                             ACZL0526
      DO 50 I=2,N1                                                      ACZL0527
      B(I)=B(I)-X(I)-AL(I)*X(I-1)-AR(I)*X(I+1)-AB(I)*X(I+N1)            ACZL0528
50    CONTINUE                                                          ACZL0529
      DO 100 I=N2,N3                                                    ACZL0530
      B(I)=B(I)-X(I)-AT(I)*X(I-N1)-AL(I)*X(I-1)-AR(I)*X(I+1)            ACZL0531
     1      -AB(I)*X(I+N1)                                              ACZL0532
100   CONTINUE                                                          ACZL0533
      DO 150 I=N4,N5                                                    ACZL0534
      B(I)=B(I)-X(I)-AT(I)*X(I-N1)-AL(I)*X(I-1)-AR(I)*X(I+1)            ACZL0535
150   CONTINUE                                                          ACZL0536
      B(N)=B(N)-X(N)-AT(N)*X(N3)-AL(N)*X(N5)                            ACZL0537
C***********************************************************************ACZL0538
C     CALCULATE L2 AND MAX NORM                                         ACZL0539
C***********************************************************************ACZL0540
      K=0                                                               ACZL0541
      ANORM=0.0                                                         ACZL0542
      BNORM=0.0                                                         ACZL0543
      DNORM=0.0                                                         ACZL0544
      DO 200 I=1,N                                                      ACZL0545
      ANORM=ANORM+B(I)*B(I)                                             ACZL0546
      DNORM=DNORM+X(I)*X(I)                                             ACZL0547
      IF(ABS(X(I)).LT.1.0E-2)  GOTO 200                                 ACZL0548
      BCOM=B(I)/X(I)                                                    ACZL0549
      IF(ABS(BCOM).GT.BNORM)  BNORM=ABS(BCOM)                           ACZL0550
200   CONTINUE                                                          ACZL0551
      ANORM=SQRT(ANORM)/SQRT(DNORM)                                     ACZL0552
      WRITE(NPM,1000) K,ANORM,BNORM                                     ACZL0553
C***********************************************************************ACZL0554
C     SET UP ITERATION LOOP.  MAXNUM IS THE MAXIMUM NUMBER OF           ACZL0555
C     ITERATION CYCLES TO BE TRIED                                      ACZL0556
C***********************************************************************ACZL0557
      NSW1=IFIX(SW1)                                                    ACZL0558
      NSW2=IFIX(SW2)                                                    ACZL0559
      MAXNUM=IFIX(FAILCN)                                               ACZL0560
      DO 950 IK=1,MAXNUM                                                ACZL0561
      K=K+1                                                             ACZL0562
      DO 850 ICY=1,5                                                    ACZL0563
      IF(NSW1.EQ.0)  GOTO 300                                           ACZL0564
      IF(NSW1.NE.1)  CALL SIPERR(2)                                     ACZL0565
      DO 250 I=1,N                                                      ACZL0566
      W(I)=ALPHA(I)*CYMULT(ICY)                                         ACZL0567
250   CONTINUE                                                          ACZL0568
      GOTO 400                                                          ACZL0569
300   CONTINUE                                                          ACZL0570
      DO 350 I=1,N                                                      ACZL0571
      W(I)=ALPHA(1)*CYMULT(ICY)                                         ACZL0572
350   CONTINUE                                                          ACZL0573
400   CONTINUE                                                          ACZL0574
C***********************************************************************ACZL0575
C     FORWARD LOOP  CALCULATES THE ELEMENTS OF L AND U, THE SPARSE      ACZL0576
C     FACTORISATION OF A+E    I.E.  LU=(A+E)  AND THEN INVERTS L        ACZL0577
C     GIVING  W=L**-1 B                                                 ACZL0578
C***********************************************************************ACZL0579
      TU1(1)=AR(1)                                                      ACZL0580
      TU2(1)=AB(1)                                                      ACZL0581
      W(1)=B(1)                                                         ACZL0582
      DO 450 I=2,N1                                                     ACZL0583
      ATU2=W(I)*TU2(I-1)                                                ACZL0584
      TL1=AL(I)/(1.0+ATU2)                                              ACZL0585
      TLD=1.0/(1.0+TL1*(ATU2-TU1(I-1)))                                 ACZL0586
      TU1(I)=AR(I)*TLD                                                  ACZL0587
      TU2(I)=(AB(I)-TL1*ATU2)*TLD                                       ACZL0588
      W(I)=(B(I)-TL1*W(I-1))*TLD                                        ACZL0589
450   CONTINUE                                                          ACZL0590
      DO 500 I=N2,N3                                                    ACZL0591
      ATU1=W(I)*TU1(I-N1)                                               ACZL0592
      ATU2=W(I)*TU2(I-1)                                                ACZL0593
      TL2=AT(I)/(1.0+ATU1)                                              ACZL0594
      TL1=AL(I)/(1.0+ATU2)                                              ACZL0595
      TLD=1.0/(1.0+TL1*(ATU2-TU1(I-1))+TL2*(ATU1-TU2(I-N1)))            ACZL0596
      TU1(I)=(AR(I)-TL2*ATU1)*TLD                                       ACZL0597
      TU2(I)=(AB(I)-TL1*ATU2)*TLD                                       ACZL0598
      W(I)=(B(I)-TL1*W(I-1)-TL2*W(I-N1))*TLD                            ACZL0599
500   CONTINUE                                                          ACZL0600
      DO 550 I=N4,N5                                                    ACZL0601
      ATU1=W(I)*TU1(I-N1)                                               ACZL0602
      TL2=AT(I)/(1.0+ATU1)                                              ACZL0603
      TLD=1.0/(1.0+TL2*(ATU1-TU2(I-N1))-AL(I)*TU1(I-1))                 ACZL0604
      TU1(I)=(AR(I)-TL2*ATU1)*TLD                                       ACZL0605
      W(I)=(B(I)-AL(I)*W(I-1)-TL2*W(I-N1))*TLD                          ACZL0606
550   CONTINUE                                                          ACZL0607
      ATU1=W(I)*TU1(N3)                                                 ACZL0608
      TL2=AT(N)/(1.0+ATU1)                                              ACZL0609
      TLD=1.0/(1.0+TL2*(ATU1-TU2(N3))-AL(N)*TU1(N5))                    ACZL0610
      W(N)=(B(N)-AL(N)*W(N5)-TL2*W(N3))*TLD                             ACZL0611
C***********************************************************************ACZL0612
C     NOW BACKWARD LOOP  INVERTS U   I.E.  W=U**-1 W                    ACZL0613
C***********************************************************************ACZL0614
      DO 600 I=2,N1                                                     ACZL0615
      J=N+1-I                                                           ACZL0616
      W(J)=W(J)-TU1(J)*W(J+1)                                           ACZL0617
600   CONTINUE                                                          ACZL0618
      DO 650 I=N2,N                                                     ACZL0619
      J=N+1-I                                                           ACZL0620
      W(J)=W(J)-TU1(J)*W(J+1)-TU2(J)*W(J+N1)                            ACZL0621
650   CONTINUE                                                          ACZL0622
C***********************************************************************ACZL0623
C     NOW UPDATE RESIDUALS                                              ACZL0624
C***********************************************************************ACZL0625
      B(1)=B(1)-W(1)-AR(1)*W(2)-AB(1)*W(N2)                             ACZL0626
      DO 700 I=2,N1                                                     ACZL0627
      B(I)=B(I)-W(I)-AL(I)*W(I-1)-AR(I)*W(I+1)-AB(I)*W(I+N1)            ACZL0628
700   CONTINUE                                                          ACZL0629
      DO 750 I=N2,N3                                                    ACZL0630
      B(I)=B(I)-W(I)-AT(I)*W(I-N1)-AL(I)*W(I-1)-AR(I)*W(I+1)            ACZL0631
     1      -AB(I)*W(I+N1)                                              ACZL0632
750   CONTINUE                                                          ACZL0633
      DO 800 I=N4,N5                                                    ACZL0634
      B(I)=B(I)-W(I)-AT(I)*W(I-N1)-AL(I)*W(I-1)-AR(I)*W(I+1)            ACZL0635
800   CONTINUE                                                          ACZL0636
      B(N)=B(N)-W(N)-AT(N)*W(N3)-AL(N)*W(N5)                            ACZL0637
C***********************************************************************ACZL0638
C     NOW UPDATE SOLUTION                                               ACZL0639
C***********************************************************************ACZL0640
      DO 825 I=1,N                                                      ACZL0641
      X(I)=X(I)+W(I)                                                    ACZL0642
825   CONTINUE                                                          ACZL0643
C***********************************************************************ACZL0644
C     END OF ITERATION                                                  ACZL0645
C***********************************************************************ACZL0646
850   CONTINUE                                                          ACZL0647
C***********************************************************************ACZL0648
C     END OF ITERATION CYCLE                                            ACZL0649
C                                                                       ACZL0650
C     CALCULATE L2 AND MAX NORM AND CHECK FOR CONVERGENCE               ACZL0651
C***********************************************************************ACZL0652
      ANORM=0.0                                                         ACZL0653
      BNORM=0.0                                                         ACZL0654
      DNORM=0.0                                                         ACZL0655
      DO 900 I=1,N                                                      ACZL0656
      ANORM=ANORM+B(I)*B(I)                                             ACZL0657
      DNORM=DNORM+X(I)*X(I)                                             ACZL0658
      IF(ABS(X(I)).LT.1.0E-2)  GOTO 900                                 ACZL0659
      BCOM=B(I)/X(I)                                                    ACZL0660
      IF(ABS(BCOM).GT.BNORM)  BNORM=ABS(BCOM)                           ACZL0661
900   CONTINUE                                                          ACZL0662
      ANORM=SQRT(ANORM)/SQRT(DNORM)                                     ACZL0663
      IF(NSW2.EQ.1)  WRITE(NPM,1000) K,ANORM,BNORM                      ACZL0664
      IF(ANORM.LT.ACC)  GOTO 999                                        ACZL0665
950   CONTINUE                                                          ACZL0666
      CALL SIPERR(7)                                                    ACZL0667
999   CONTINUE                                                          ACZL0668
C***********************************************************************ACZL0669
C     HAVE NOW ACHIEVED EXIT ON ACCURACY OR COUNT                       ACZL0670
C***********************************************************************ACZL0671
      IF(NSW2.NE.1)  WRITE(NPM,1000)K-1,ANORM,BNORM                     ACZL0672
      RETURN                                                            ACZL0673
C***********************************************************************ACZL0674
C     FORMATS                                                           ACZL0675
C***********************************************************************ACZL0676
1000  FORMAT(1H ,                                                       ACZL0677
     15HCYCLE,I3,                                                       ACZL0678
     111H L2 NORM = ,1PE10.3,                                           ACZL0679
     112H MAX NORM = ,1PE10.3,                                          ACZL0680
     1)                                                                 ACZL0681
C***********************************************************************ACZL0682
      END                                                               ACZL0683


#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE1="1.txt"
TEST_FILE2="2.txt 3.txt"
echo "" >s21_grep_errors.txt

echo "_OPTIONS -i -v -c -l -n -h_"

for var in -i -v -c -l -n -h; do
  for pattern in 123 girl. The "o$" could "d[a-z][a-z]" "\w," terr; do
    TEST1="$var $pattern $TEST_FILE1 $TEST_FILE2"
    echo "$TEST1"
    ./s21_grep $TEST1 >s21_grep.txt
    grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_grep_errors.txt
              (( COUNTER_FAIL++ ))
          fi
    TEST1="$pattern $var $TEST_FILE1 $TEST_FILE2"
    echo "$TEST1"
    ./s21_grep $TEST1 >s21_grep.txt
    grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_grep_errors.txt
              (( COUNTER_FAIL++ ))
          fi

    TEST1="$pattern $TEST_FILE1 $var $TEST_FILE2"
    echo "$TEST1"
    ./s21_grep $TEST1 >s21_grep.txt
    grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_grep_errors.txt
              (( COUNTER_FAIL++ ))
          fi

    TEST1="$pattern $TEST_FILE1 $TEST_FILE2 $var"
    echo "$TEST1"
    ./s21_grep $TEST1 >s21_grep.txt
    grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_grep_errors.txt
              (( COUNTER_FAIL++ ))
          fi

    rm s21_grep.txt
    rm grep.txt
  done
done

echo "_OPTION -e_"

for pattern1 in girl. The could "d[a-z][a-z]" "\w," terr; do
  for pattern2 in 123 suppositions "o$" assembly gentle "six." terr; do
    TEST1="-e $pattern1 $TEST_FILE1 -e $pattern2 $TEST_FILE2"
    echo "$TEST1"
    ./s21_grep $TEST1 >s21_grep.txt
    grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_grep_errors.txt
              (( COUNTER_FAIL++ ))
          fi

    rm s21_grep.txt
    rm grep.txt
  done
done

echo "_OPTION -f_"
TEST1="-f pat.txt $TEST_FILE1 $TEST_FILE2"
echo "$TEST1"
./s21_grep $TEST1 > s21_grep.txt
grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_grep_errors.txt
              (( COUNTER_FAIL++ ))
          fi

rm s21_grep.txt
rm grep.txt

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
if [ "$COUNTER_FAIL" != 0 ]; then
	exit 1
else
	exit 0
fi

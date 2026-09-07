COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="0.txt"
TEST_FILE1="1.txt"
TEST_FILE2="2.txt"
TEST_FILE3="3.txt"
echo "" > s21_cat_errors.txt

echo "_ONE OPTION_"

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_cat_errors.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
done

echo "_TWO OPTIONS_"

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE $TEST_FILE1"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> s21_cat_errors.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
if [ "$COUNTER_FAIL" !=  0 ]; then
	exit 1
else
	exit 0
fi

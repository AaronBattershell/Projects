package com.amb288.trivia;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class Trivia extends ActionBarActivity {
    /* Make sure to update totalQuestions as you add more questions*/
    private int totalQuestions = 5;
    private int correct = 0, wrong = 0;

    /* Under most casts we would want a unique identifier for the startActivityForResults function
     * call but in this situation it is not needed */
    private int NEW_QUESTION = 1;

    private TextView score = null;
    private Button firstQuestion = null;
    private Button secondQuestion = null;
    private Button thirdQuestion = null;
    private Button foruthQuestion = null;
    private Button lastQuestion = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trivia);

        score = (TextView) findViewById(R.id.userScore);
        firstQuestion = (Button) findViewById(R.id.testRadioButton);
        secondQuestion = (Button) findViewById(R.id.testSpinnerButton);
        thirdQuestion = (Button) findViewById(R.id.testSpinnerButton2);
        foruthQuestion = (Button) findViewById(R.id.testSpinnerButton3);
        lastQuestion = (Button) findViewById(R.id.testSpinnerButton4);


        Button testRadioBtnActivity = (Button) findViewById(R.id.testRadioButton);
        testRadioBtnActivity.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an intent stating which Activity you would like to start
                Intent intent = new Intent(Trivia.this, RadioQuestionActivity.class);

                String[] answers = { "A Leek", " A Welsh Onion", "Garlic", "Ichigo Kurosaki" };
                intent.putExtra("question", "What object Spins in the LeekSpin Animation?");
                intent.putExtra("selection", answers); /* For radio button always add 4 entries. No more, and no less.*/
                intent.putExtra("answer", 2); /* 1 based answer index in the array */

                /* Lock the button you pressed so the user can't answer that question more than once */
                firstQuestion.setEnabled(false);

                // Launch the Activity using the intent
                startActivityForResult(intent, NEW_QUESTION);
            }
        });

        Button testSpinnerActivity = (Button) findViewById(R.id.testSpinnerButton);
        testSpinnerActivity.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an intent stating which Activity you would like to start
                Intent intent = new Intent(Trivia.this, SpinnerQuestionActivity.class);

                String[] answers = {"Ichigo Kurosaki", "Chuck Noris", "Orihime Inoue", "Goku", "Null Reference Exception" };
                intent.putExtra("question", "What anime Character is featured in the LeekSpin animation?");
                intent.putExtra("selection", answers); /* For spinner questions add as many entries as you want*/
                intent.putExtra("answer", 3); /* 1 based answer index in the array */

                /* Lock the button you pressed so the user can't answer that question more than once */
                secondQuestion.setEnabled(false);

                // Launch the Activity using the intent
                startActivityForResult(intent, NEW_QUESTION);
            }
        });

        Button testSpinnerActivity2 = (Button) findViewById(R.id.testSpinnerButton2);
        testSpinnerActivity2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an intent stating which Activity you would like to start
                Intent intent = new Intent(Trivia.this, SpinnerQuestionActivity.class);

                String[] answers = {"2", "3", "4", "5", "6", "7", "56", "784" };
                intent.putExtra("question", "How many frames does the Leekspin animation have?");
                intent.putExtra("selection", answers); /* For spinner questions add as many entries as you want*/
                intent.putExtra("answer", 3); /* 1 based answer index in the array */

                /* Lock the button you pressed so the user can't answer that question more than once */
                thirdQuestion.setEnabled(false);

                // Launch the Activity using the intent
                startActivityForResult(intent, NEW_QUESTION);
            }
        });

        Button testRadioBtnActivity2 = (Button) findViewById(R.id.testSpinnerButton3);
        testRadioBtnActivity2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an intent stating which Activity you would like to start
                Intent intent = new Intent(Trivia.this, RadioQuestionActivity.class);

                String[] answers = { "Ievan Polkka by Loituma", "Cocaine by Nightcore", "Gōrudentaimurabā by Sukima Switch", "Sekai no Kami Desu YO! by Kami" };
                intent.putExtra("question", "what delightful music plays in the background during leekspin?");
                intent.putExtra("selection", answers); /* For radio button always add 4 entries. No more, and no less.*/
                intent.putExtra("answer", 1); /* 1 based answer index in the array */

                /* Lock the button you pressed so the user can't answer that question more than once */
                foruthQuestion.setEnabled(false);

                // Launch the Activity using the intent
                startActivityForResult(intent, NEW_QUESTION);
            }
        });

        Button testRadioBtnActivity3 = (Button) findViewById(R.id.testSpinnerButton3);
        testRadioBtnActivity3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an intent stating which Activity you would like to start
                Intent intent = new Intent(Trivia.this, RadioQuestionActivity.class);

                String[] answers = { "15 Seconds", "1 Minute 12 Seconds", "27 Seconds", "48 Seconds", "52 Seconds", "23 Seconds" };
                intent.putExtra("question", "How Long is each leekspin music loop?");
                intent.putExtra("selection", answers); /* For radio button always add 4 entries. No more, and no less.*/
                intent.putExtra("answer", 3); /* 1 based answer index in the array */

                /* Lock the button you pressed so the user can't answer that question more than once */
                lastQuestion.setEnabled(false);

                // Launch the Activity using the intent
                startActivityForResult(intent, NEW_QUESTION);
            }
        });

    }



    /* Receive the return results from the activities that have been called */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        /* Since all we care about is a boolean value I am disregarding the requestCode and
         * Intent variable. If the user answered the correct value then resultCode will be
         * the enum RESULT_OK */
        if (resultCode == RESULT_OK) {
            ++correct;
        }
        else {
            ++wrong;
        }

        score.setText(String.format("%.2f", (correct/(double)(correct+wrong))*100.0) + "%");

        /* Display the end of game results, then reset all values when returned to this activity */
        if (correct + wrong == totalQuestions) {
            Intent intent = new Intent(Trivia.this, displayResults.class);
            intent.putExtra("score", correct/(double)(correct+wrong));
            startActivity(intent);

            // Reset all values
            firstQuestion.setEnabled(true);
            secondQuestion.setEnabled(true);
            thirdQuestion.setEnabled(true);
            foruthQuestion.setEnabled(true);
            lastQuestion.setEnabled(true);
            correct = 0;
            wrong = 0;
        }
    }
}

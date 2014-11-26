package com.amb288.trivia;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

/**
 * Created by macho man Randy Savage on 11/16/2014.
 */
public class displayResults extends Activity {
    private Button backBtn = null;
    private TextView statementLbl = null;
    private TextView resultLbl = null;
    private Bundle extras = null;
    private double score = 0.0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.results_layout);

        backBtn = (Button) findViewById(R.id.back);
        statementLbl = (TextView) findViewById(R.id.statement);
        resultLbl = (TextView) findViewById(R.id.result);
        extras = getIntent().getExtras();

        if (extras != null) {
            score = extras.getDouble("score");
            statementLbl.setText("Score results: " + (score*100) + "%");
            resultLbl.setText("Status Ranking: " + getResult(score));
        }

        Button returnBtn = (Button) findViewById(R.id.back);
        returnBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
    }

    String getResult(double score) {
        if (score == 1) {
            return "World Champion";
        }
        else if (score >= 0.80) {
            return "Aspiring Scholar";
        }
        else if (score >= 0.70) {
            return "Average Joe";
        }
        else if (score >= 0.60) {
            return "Knowledgeable Muffin";
        }
        else if (score >= 0.50) {
            return "Mopey Zoo Lion";
        }
        else {
            return "Random Number Generator";
        }
    }
}

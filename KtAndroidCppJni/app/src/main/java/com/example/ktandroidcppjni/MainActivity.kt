package com.example.ktandroidcppjni

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.example.ktandroidcppjni.ui.theme.KtAndroidCppJniTheme

class MainActivity : ComponentActivity() {

    private val mainViewModel: MainViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            KtAndroidCppJniTheme {
                Scaffold(
                    modifier = Modifier.fillMaxSize()
                ) { innerPadding ->
                    MainScreenPage(
                        mainViewModel,
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

@Composable
fun MainScreenPage(
    viewModel: MainViewModel,
    modifier: Modifier = Modifier
) {
    val showText = viewModel.showText.collectAsStateWithLifecycle()

    MainScreen(
        name = showText.value,
        onTestClick = {
            viewModel.testRun()
        },
        modifier = modifier
    )
}

@Composable
fun MainScreen(
    name: String,
    onTestClick: () -> Unit,
    modifier: Modifier = Modifier
) {
    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center,
        modifier = modifier.fillMaxSize()
    ) {
        Text(
            text = "Text: $name",
            modifier = Modifier.padding(bottom = 6.dp)
        )
        Button(
            onClick = { onTestClick() },
        ) {
            Text("Click")
        }
    }
}

@Preview(showBackground = true)
@Composable
fun MainScreenPreview() {
    KtAndroidCppJniTheme {
        MainScreen(
            name = "Android",
            onTestClick = {})
    }
}
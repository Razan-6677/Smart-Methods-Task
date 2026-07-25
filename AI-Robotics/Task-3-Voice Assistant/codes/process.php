<?php
header('Content-Type: application/json; charset=utf-8');

require __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    echo json_encode(['error' => 'الطريقة غير مسموحة']);
    exit;
}

$input  = json_decode(file_get_contents('php://input'), true);
$prompt = isset($input['prompt']) ? trim($input['prompt']) : '';

if ($prompt === '') {
    http_response_code(400);
    echo json_encode(['error' => 'الرجاء إرسال نص صالح في الحقل prompt']);
    exit;
}

if (!defined('GEMINI_API_KEY') || GEMINI_API_KEY === 'ضع_مفتاحك_الحقيقي_هنا_يبدأ_بـ_AIzaSy') {
    http_response_code(500);
    echo json_encode(['error' => 'لم يتم ضبط مفتاح Gemini في config.php بعد']);
    exit;
}

$model = 'gemini-3.5-flash';
$url   = "https://generativelanguage.googleapis.com/v1beta/models/{$model}:generateContent?key=" . GEMINI_API_KEY;

$body = json_encode([
    'contents' => [
        ['parts' => [['text' => $prompt]]],
    ],
]);

$ch = curl_init($url);
curl_setopt_array($ch, [
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_POST           => true,
    CURLOPT_HTTPHEADER     => ['Content-Type: application/json'],
    CURLOPT_POSTFIELDS     => $body,
    CURLOPT_TIMEOUT        => 25,
    CURLOPT_SSL_VERIFYPEER => false,
    CURLOPT_SSL_VERIFYHOST => false,
]);

$response = curl_exec($ch);
$httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
$curlErr  = curl_error($ch);
curl_close($ch);

if ($response === false) {
    http_response_code(502);
    echo json_encode(['error' => 'فشل الاتصال بـ Gemini API: ' . $curlErr]);
    exit;
}

$data = json_decode($response, true);

if ($httpCode >= 400 || $data === null) {
    http_response_code(502);
    echo json_encode(['error' => 'رفض Gemini API الطلب', 'details' => $data ?? $response]);
    exit;
}

$reply = $data['candidates'][0]['content']['parts'][0]['text'] ?? 'تعذر الحصول على رد من Gemini.';

echo json_encode(['reply' => $reply], JSON_UNESCAPED_UNICODE);
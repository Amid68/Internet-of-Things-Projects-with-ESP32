# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
"""
System test framework for multi-LED validation
"""

import logging
import os
import pytest
from pytest_embedded_idf import IdfDut

LED_CYCLE_COUNT = 3
VALIDATION_TIMEOUT = 60

@pytest.mark.supported_targets
@pytest.mark.generic
@pytest.mark.parametrize('config', ['gpio', 'led_strip'], indirect=True)
def test_led_operation(dut: IdfDut) -> None:
    """
    Validate LED operation patterns and system stability
    """
    # Binary size validation
    bin_path = os.path.join(dut.app.binary_path, f'{dut.app.name}.bin')
    bin_size = os.path.getsize(bin_path)
    logging.info('Application binary size: %.2fKB', bin_size / 1024)
    assert bin_size < 1.5 * 1024 * 1024, "Binary size exceeds safety limit"

    # LED operation pattern validation
    for cycle in range(LED_CYCLE_COUNT):
        expected_state = 'ACTIVE' if (cycle % 2) == 0 else 'INACTIVE'
        for led in range(1, 4):
            dut.expect(f'LED {led} state: {expected_state}', timeout=VALIDATION_TIMEOUT)

    # System stability check
    assert 'CPU halted' not in dut.processed_output, "System instability detected"